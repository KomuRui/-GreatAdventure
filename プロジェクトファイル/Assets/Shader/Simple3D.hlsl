//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture: register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	g_matWVP;			  // ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matNormalTrans;	  // 法線の変換行列（回転行列と拡大の逆行列）
	float4x4	g_matWorld;			  // ワールド変換行列
	float4		g_vecLightDir;		  // ライトの方向ベクトル
	float4		g_vecDiffuse;		  // ディフューズカラー（マテリアルの色）
	float4		g_vecAmbient;		  // アンビエントカラー（影の色）
	float4		g_vecSpeculer;		  // スペキュラーカラー（ハイライトの色）
	float4      g_isSpeculerColor;    // 任意で決めれるスペキュラーカラー
	float4		g_vecCameraPosition;  // 視点（カメラの位置）
	float4      g_vecLightPosition;   // ライトの位置
	float4      g_LightPosition[15];  // ライトの個数分の位置
	float4      g_LightIntensity[15]; // ライトの個数分の強さ
	float4      g_isAmbient;          // アンビエントの力の大きさ 
	float4		g_outLineColor;		  //アウトラインの色
	float		g_shuniness;		  // ハイライトの強さ（テカリ具合）
	bool		g_isTexture;		  // テクスチャ貼ってあるかどうか
	float 		g_isDiffuse;		  // 透明にするか
	float       g_isBrightness;       // 明るさ
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float4 normal : TEXCOORD2;		//法線
	float2 uv	  : TEXCOORD0;		//UV座標
	float4 eye	  : TEXCOORD1;		//視線
	float4 norw   : TEXCOORD3;      //ワールドマトリクスだけかけた法線
	float4 posw   : TEXCOORD4;      //ワールドマトリクスだけかけた位置
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	outData.posw = mul(pos, g_matWorld);

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, g_matWVP);		

	//法線の変形
	Normal.w = 0;					            //4次元目は使わないので0
	Normal = mul(Normal, g_matNormalTrans);		//オブジェクトが変形すれば法線も変形
	outData.normal = Normal;		            //これをピクセルシェーダーへ
	outData.norw = mul(Normal, g_matWorld);

	//視線ベクトル（ハイライトの計算に必要
	float4 worldPos = mul(pos, g_matWorld);					    //ローカル座標にワールド行列をかけてワールド座標へ
	outData.eye = normalize(g_vecCameraPosition - worldPos);	//視点から頂点位置を引き算し視線を求めてピクセルシェーダーへ

	//UV「座標
	outData.uv = Uv;	//そのままピクセルシェーダーへ


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	//ライトの向き
	float4 lightDir = g_vecLightDir;	//グルーバル変数は変更できないので、いったんローカル変数へ
	lightDir = normalize(lightDir);     //向きだけが必要なので正規化

	//法線はピクセルシェーダーに持ってきた時点で補完され長さが変わっている
	//正規化しておかないと面の明るさがおかしくなる
	inData.normal.w = 0;
	inData.normal = normalize(inData.normal);

	float3 dir = float3(0,0,0);
	float3 sumDir = float3(0, 0, 0); //すべての光源の方向を考慮した方向
	float  len = 0;
	float  colD = 0;
	float  colA = 0;
	float  col = 0;
	float4 shade = float4(0,0,0,0);

	for (int i = 0; i < 8; i++)
	{
		if (g_LightPosition[i].x != 99999 && g_LightPosition[i].y != 99999 && g_LightPosition[i].z != 99999)
		{
			//点光源の方向
			dir = g_LightPosition[i].xyz - inData.posw.xyz;

			//点光源の距離
			len = length(dir) / g_LightIntensity[i];

			//点光源の方向をnormalize
			dir = normalize(dir);

			//方向を足す
			sumDir += dir;
			sumDir = normalize(sumDir);

			//拡散
			colD = saturate(dot(normalize(inData.normal), dir)) * g_LightIntensity[i];

			//減衰
			colA = saturate(1.0f / (1.0 + 0 * len + 0.2 * len * len));

			col += colD * colA;
		}
	}

	if (col > 1)
		col = 1;

	if (g_isBrightness == 0)
		shade = float4(col, col, col, 1.0f);
	else
		shade = float4(g_isBrightness, g_isBrightness, g_isBrightness, 1.0f);


	float4 d = float4(sumDir.x, sumDir.y, sumDir.z, 0);

	float4 diffuse;
	//テクスチャ有無
	if (g_isTexture == true)
	{
		//テクスチャの色
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		//マテリアルの色
		diffuse = g_vecDiffuse;
	}

	//環境光（アンビエント）
	//これはMaya側で指定し、グローバル変数で受け取ったものをそのまま
	float4 	ambient = g_vecAmbient;

	//鏡面反射光（スペキュラー）
	float4 speculer = g_isSpeculerColor;	//とりあえずハイライトは無しにしておいて…

	if (g_isBrightness == 0)
	{
		if (g_vecSpeculer.a != 0)	//スペキュラーの情報があれば
		{
			float4 R = reflect(d, inData.normal);			//正反射ベクトル
			speculer = pow(saturate(dot(R, inData.eye)), g_shuniness) * g_vecSpeculer;	//ハイライトを求める
		}
	}

	//最終的な色
	float4 color = diffuse * shade + diffuse * ambient + speculer;
	color += g_isAmbient;
	color.a = g_isDiffuse;

	return color;
}