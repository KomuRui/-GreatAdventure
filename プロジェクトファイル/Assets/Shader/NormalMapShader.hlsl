//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture: register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー
Texture2D g_textureNormal : register(t1);   //ノーマルテクスチャー


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
	float       g_scroll;             // スクロール値
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv	  : TEXCOORD1;		//UV座標
	float4 light  : TEXCOORD2;		//ライトの方向
	float4 V      : TEXCOORD3;		//頂点からカメラに向かうベクトル
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD, float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, g_matWVP);
         
	//UV「座標
	outData.uv = uv;	//そのままピクセルシェーダーへ

	//法線
	normal.w = 0;
	normal = mul(normal, g_matNormalTrans);
	normal = normalize(normal);

	//タンジェント
	tangent.w = 0;
	tangent = mul(tangent, g_matNormalTrans);
	tangent = normalize(tangent);

	//バイノーマル
	float3 binormal = cross(normal, tangent);
	binormal = normalize(binormal);

	//頂点からカメラに向かうベクトル(正規化)
	float4 eye = normalize(mul(pos, g_matWorld) - g_vecCameraPosition);
	outData.V.x = dot(eye, tangent);
	outData.V.y = dot(eye, binormal);
	outData.V.z = dot(eye, normal);
	outData.V.w = 0;

	////ライトの方向
	float4 light = g_vecLightPosition - pos;
	light = normalize(light);
	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{

	//正規化しておく
	inData.light = normalize(inData.light);
	float alpha = 0;

	float2 uv1 = inData.uv;
	uv1.x += g_scroll;
	float4 normal1 = g_textureNormal.Sample(g_sampler, uv1) * 2 - 1;

	float2 uv2 = inData.uv;
	uv2.x -= g_scroll * 0.3;
	float4 normal2 = g_textureNormal.Sample(g_sampler, uv2) * 2 - 1;

	float4 normal = normal1 + normal2;
	normal.w = 0;
	normal = normalize(normal);

	float4 shade = dot(normal, inData.light);
	shade = clamp(shade, 0, 1);

	float4 diffuse;
	//テクスチャ有無
	if (g_isTexture == true)
	{
		//テクスチャの色
		diffuse = g_texture.Sample(g_sampler, inData.uv);
		alpha = g_texture.Sample(g_sampler, inData.uv).a;
	}
	else
	{
		//マテリアルの色
		diffuse = g_vecDiffuse;
	}

	//環境光（アンビエント）
	//これはMaya側で指定し、グローバル変数で受け取ったものをそのまま
	float4 	ambient = float4(0.5, 0.5, 0.5, 1);g_vecAmbient * g_isAmbient;

	//鏡面反射光（スペキュラー）
	float4 speculer = float4(1, 1, 1, 1);	

	float4 R = reflect(inData.light, normal);		//正反射ベクトル
	speculer = pow(saturate(dot(R, inData.V)), 5) * 3;//ハイライトを求める


	//最終的な色
	float4 color = diffuse * shade + diffuse * ambient + speculer;
	color.a = alpha;

	return color;
}