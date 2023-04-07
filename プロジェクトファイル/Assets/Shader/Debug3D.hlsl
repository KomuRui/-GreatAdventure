// 定数バッファ(CPU側からの値受け取り場)
cbuffer global
{
	float4x4	WVP;    // 変換行列
};

// 頂点シェーダ
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	return mul(pos, WVP);	
}

// ピクセルシェーダ
float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return float4(0.7, 0.7, 0.7, 0.5);
}