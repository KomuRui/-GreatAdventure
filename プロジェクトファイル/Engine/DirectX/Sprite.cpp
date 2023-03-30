#include "Sprite.h"
#include "Direct3D.h"
#include "../ResourceManager/Global.h"
#include "../GUI/ImGuiSet.h"

//コンストラクタ
Sprite::Sprite():
	pTexture_(nullptr)
{
}

//デストラクタ
Sprite::~Sprite()
{

	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
}

//準備
HRESULT Sprite::Load(std::string fileName)
{
	//テクスチャ準備
	pTexture_ = new Texture();
	if(FAILED(pTexture_->Load(fileName)))
	{
		return E_FAIL;
	}

	//頂点情報準備
	InitVertex();

	//インデックス情報準備
	InitIndex();
	
	//コンスタントバッファ準備
	InitConstantBuffer();

	return S_OK;
}

HRESULT Sprite::Initialize(ID3D11Texture2D* pTexture)
{
	pTexture_ = new Texture;
	pTexture_->Load(pTexture);

	// 頂点情報
	InitVertex();

	//インデックス情報
	InitIndex();

	//コンスタントバッファ作成
	InitConstantBuffer();

	return S_OK;
}

//コンスタントバッファ準備
void Sprite::InitConstantBuffer()
{
	//必要な設定項目
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth =		sizeof(CONSTANT_BUFFER);
	cb.Usage =			D3D11_USAGE_DYNAMIC;
	cb.BindFlags =		D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags =		0;
	cb.StructureByteStride = 0;

	// 定数バッファの作成
	Direct3D::pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer_);
}


void Sprite::InitVertex()
{
	// 頂点データ宣言
	VERTEX vertices[] =
	{
		{ XMFLOAT3(-1.0f,  1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f) },   // 四角形の頂点（左上）
		{ XMFLOAT3( 1.0f,  1.0f, 0.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },   // 四角形の頂点（右上）
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },   // 四角形の頂点（左下）
		{ XMFLOAT3( 1.0f, -1.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 0.0f) },   // 四角形の頂点（右下）
	};


	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

void Sprite::InitIndex()
{
	int index[] = {2,1,0, 2,3,1 };

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
}

void Sprite::Draw(Transform& transform, RECT rect, float alpha)
{
	transform.Calclation();

	//いろいろ設定
	Direct3D::SetShader(Direct3D::SHADER_2D);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::SetDepthBafferWriteEnable(false);


	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	// パラメータの受け渡し
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;


	//表示するサイズに合わせる
	XMMATRIX cut = XMMatrixScaling((float)rect.right, (float)rect.bottom ,1);

	//画面に合わせる
	XMMATRIX view = XMMatrixScaling(1.0f / Direct3D::screenWidth_, 1.0f / Direct3D::screenHeight_, 1.0f);

	//最終的な行列
	XMMATRIX world = (cut * transform.matScale_ * transform.matRotate_ * view * transform.matTranslate_) * transform.GetParentWorldMatrix();
	cb.world = XMMatrixTranspose(world);

	// テクスチャ座標変換行列を渡す
	XMMATRIX mTexTrans = XMMatrixTranslation((float)rect.left / (float)pTexture_->GetSize().x,
		(float)rect.top / (float)pTexture_->GetSize().y, 0.0f);
	XMMATRIX mTexScale = XMMatrixScaling((float)rect.right / (float)pTexture_->GetSize().x,
		(float)rect.bottom / (float)pTexture_->GetSize().y, 1.0f);
	XMMATRIX mTexel = mTexScale * mTexTrans;
	cb.uvTrans = XMMatrixTranspose(mTexel);
	

	// テクスチャ合成色情報を渡す
	cb.color = XMFLOAT4(1, 1, 1, alpha);

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// リソースへ値を送る


	ID3D11SamplerState*			pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView*	pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);									// GPUからのリソースアクセスを再開

	//ポリゴンメッシュを描画する
	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	Direct3D::SetShader(Direct3D::SHADER_3D);

	Direct3D::SetDepthBafferWriteEnable(true);

}

void Sprite::Draw(Transform& transform, float dis, RECT rect)
{
	//トランスふぇーむ計算する
	transform.Calclation();

	//いろいろ設定
	Direct3D::SetShader(Direct3D::SHADER_FADE_IN);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::SetDepthBafferWriteEnable(false);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	// パラメータの受け渡し
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;


	//表示するサイズに合わせる
	XMMATRIX cut = XMMatrixScaling((float)rect.right, (float)rect.bottom, 1);

	//画面に合わせる
	XMMATRIX view = XMMatrixScaling(1.0f / Direct3D::screenWidth_, 1.0f / Direct3D::screenHeight_, 1.0f);

	//最終的な行列
	XMMATRIX world = cut * transform.matScale_ * transform.matRotate_ * view * transform.matTranslate_;
	cb.world = XMMatrixTranspose(world);

	// テクスチャ座標変換行列を渡す
	XMMATRIX mTexTrans = XMMatrixTranslation((float)rect.left / (float)pTexture_->GetSize().x,
		(float)rect.top / (float)pTexture_->GetSize().y, 0.0f);
	XMMATRIX mTexScale = XMMatrixScaling((float)rect.right / (float)pTexture_->GetSize().x,
		(float)rect.bottom / (float)pTexture_->GetSize().y, 1.0f);
	XMMATRIX mTexel = mTexScale * mTexTrans;
	cb.uvTrans = XMMatrixTranspose(mTexel);

	// テクスチャ合成色情報を渡す
	cb.color = XMFLOAT4(1, 1, 1, 1);

	//距離を入れる
	cb.distance = dis;

	//スクリーンの横と縦の長さ入れる
	if (Direct3D::GetGameFull())
	{
		cb.screenWidth = Direct3D::screenWidth_ / 2.0f;
		cb.screenHeight = Direct3D::screenHeight_ / 2.0f;
	}
	//マップエディタ状態なら
	else
	{
		cb.screenWidth = (Direct3D::screenWidth_ / 1.5f)/ 2.0f;
		cb.screenHeight = (Direct3D::screenHeight_ / 1.5f) / 2.0f + 100;
	}

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// リソースへ値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	// GPUからのリソースアクセスを再開

	//ポリゴンメッシュを描画する
	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	Direct3D::SetShader(Direct3D::SHADER_3D);

	Direct3D::SetDepthBafferWriteEnable(true);

}

void Sprite::Draw(Transform& transform,float alpha)
{
	//いろいろ設定
	Direct3D::SetShader(Direct3D::SHADER_2D);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::SetDepthBafferWriteEnable(false);


	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	// パラメータの受け渡し
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;


	//画面に合わせる
	//XMMATRIX view = XMMatrixScaling(1.0f / Direct3D::screenWidth_, 1.0f / Direct3D::screenHeight_, 1.0f);

	//最終的な行列
	//XMMATRIX world = transform.matScale_ * transform.matRotate_ /** view*/ * transform.matTranslate_;
	//cb.world = XMMatrixTranspose(world);


	// テクスチャ合成色情報を渡す
	cb.color = XMFLOAT4(1, 1, 1, alpha);

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// リソースへ値を送る


	/*ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);*/

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);									// GPUからのリソースアクセスを再開

	//ポリゴンメッシュを描画する
	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	Direct3D::SetShader(Direct3D::SHADER_3D);

	Direct3D::SetDepthBafferWriteEnable(true);

}

void Sprite::Draw(Transform& transform)
{
	Direct3D::SetShader(Direct3D::SHADER_2D);

	XMMATRIX scaleMatrix = XMMatrixScaling((float)pTexture_->GetSize().x / Direct3D::screenWidth_, (float)pTexture_->GetSize().y / Direct3D::screenHeight_, 1.0f);

	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	cb.world = XMMatrixTranspose(scaleMatrix * transform.GetWorldMatrix());
	cb.uvTrans = XMMatrixTranspose(XMMatrixIdentity());
	cb.color = XMFLOAT4(1, 1, 1, 1);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る


	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(6, 0, 0);
}

//色を反転する(透明色は指定した色にその他の色は透明に)
void Sprite::ReversalColorDraw(Transform& transform, RECT rect, XMFLOAT4 color)
{
	//トランスふぇーむ計算する
	transform.Calclation();

	//いろいろ設定
	Direct3D::SetShader(Direct3D::SHADER_REVERS_COLOR);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::SetDepthBafferWriteEnable(false);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	// パラメータの受け渡し
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;


	//表示するサイズに合わせる
	XMMATRIX cut = XMMatrixScaling((float)rect.right, (float)rect.bottom, 1);

	//画面に合わせる
	XMMATRIX view = XMMatrixScaling(1.0f / Direct3D::screenWidth_, 1.0f / Direct3D::screenHeight_, 1.0f);

	//最終的な行列
	XMMATRIX world = cut * transform.matScale_ * transform.matRotate_ * view * transform.matTranslate_;
	cb.world = XMMatrixTranspose(world);

	// テクスチャ座標変換行列を渡す
	XMMATRIX mTexTrans = XMMatrixTranslation((float)rect.left / (float)pTexture_->GetSize().x,
		(float)rect.top / (float)pTexture_->GetSize().y, 0.0f);
	XMMATRIX mTexScale = XMMatrixScaling((float)rect.right / (float)pTexture_->GetSize().x,
		(float)rect.bottom / (float)pTexture_->GetSize().y, 1.0f);
	XMMATRIX mTexel = mTexScale * mTexTrans;
	cb.uvTrans = XMMatrixTranspose(mTexel);

	// テクスチャ合成色情報を渡す
	cb.color = color;

	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// リソースへ値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	// GPUからのリソースアクセスを再開

	//ポリゴンメッシュを描画する
	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	Direct3D::SetShader(Direct3D::SHADER_3D);

	Direct3D::SetDepthBafferWriteEnable(true);
}