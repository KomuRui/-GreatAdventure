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
	int   g_isTwoCamera;   // 二つ目のカメラかどうか
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

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 diffuse = g_texture.Sample(g_sampler, input.uv);
	float Alpha = diffuse.a;

	if (g_isTwoCamera >= 1)
	{
		float a;

		if (g_isTwoCamera == 1)
		{
			a = ((input.pos.x - (340)) * (input.pos.x - (340))) + ((input.pos.y - (255)) * (input.pos.y - (255)));
		}
		
		if(g_isTwoCamera == 2)
		{
			a = ((input.pos.x - (1300)) * (input.pos.x  - (1300))) + ((input.pos.y - (255)) * (input.pos.y  - (255)));
		}
		float b = (250 * 250);
		if ( a > b )
		{
			diffuse.a = 0;
			return diffuse; 
		}
		else
		{
			float c = b / a;

			if(Alpha != 0)
			diffuse.a = c - 1;
		}

	}

  return g_vecColor * diffuse;
}