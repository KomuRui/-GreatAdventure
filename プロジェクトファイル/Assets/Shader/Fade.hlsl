//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0);	// テクスチャー
SamplerState g_sampler : register(s0); // テクスチャーサンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	matrix g_matWorld;		// 頂点座標変換行列
	matrix g_matTexture;	// テクスチャ座標変換行列
	float4 g_vecColor;		// テクスチャ合成色
	float  g_distance;      // 描画距離
	float  g_screenWidth;   // スクリーンの横
	float  g_screenHeight;  // スクリーンの縦
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUTPUT
{
	float4 pos	: SV_POSITION;	// 位置
	float2 uv	: TEXCOORD;		// UV座標
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUTPUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
	VS_OUTPUT output;
	output.pos = mul(pos, g_matWorld);
	output.uv = mul(uv, g_matTexture);
	return output;
}

//////////////////////////////////FadeIn用///////////////////////////////////////////

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS_FadeIn(VS_OUTPUT input) : SV_Target
{
	float4 diffuse = g_texture.Sample(g_sampler, input.uv);
	float Alpha = diffuse.a;

	float dis = ((input.pos.x - g_screenWidth) * (input.pos.x - g_screenWidth)) + ((input.pos.y - g_screenHeight) * (input.pos.y - g_screenHeight));

	//描画距離より小さいなら
	if ((g_distance * g_distance) > dis)
	{
		float4 color = g_vecColor * diffuse;
		color.a = 0;

		return color;
	}
	else
	{
		float4 color = g_vecColor * diffuse;
		color.a = 1;

		return color;
	}
}

//////////////////////////////////FadeOut用///////////////////////////////////////////

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS_FadeOut(VS_OUTPUT input) : SV_Target
{
	float4 diffuse = g_texture.Sample(g_sampler, input.uv);
	float Alpha = diffuse.a;

	float dis = ((input.pos.x - g_screenWidth) * (input.pos.x - g_screenWidth)) + ((input.pos.y - g_screenHeight) * (input.pos.y - g_screenHeight));

	//描画距離より小さいなら
	if ((g_distance * g_distance) > dis)
	{
		float4 color = g_vecColor * diffuse;
		color.a = 1;

		return color;
	}
	else
	{
		float4 color = g_vecColor * diffuse;
		color.a = 0;

		return color;
	}

}
