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
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//法線
	normal.w = 0;
	pos = pos + normal * 0.2f;
	outData.pos = mul(pos, g_matWVP);

	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	return g_outLineColor;
}