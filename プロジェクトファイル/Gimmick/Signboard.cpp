#include "Signboard.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Engine/ImGuiSet.h"

//定数
namespace
{
	static int ROTATION_ANGLE_Y = 180; //Y軸の回転角度
}

//コンストラクタ
Signboard::Signboard(GameObject* parent,std::string fileName,std::string name)
    :GameObject(parent, name),
	pVertexBuffer_(nullptr),pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), polySize_(5.0f), fileName_(fileName), isLookCamera_(false)
{
}

//画像をロードしてポリゴンを作成
HRESULT Signboard::Load()
{
	HRESULT hr;

	// 頂点情報
	VERTEX vertices[] =
	{
		{ XMFLOAT3(-5.0f,  5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(0.0f, 0.0f, 0.0f) },   // 四角形の頂点（左上）
		{ XMFLOAT3(5.0f,  5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(1.0f, 0.0f, 0.0f) },   // 四角形の頂点（右上）
		{ XMFLOAT3(5.0f, -5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(1.0f, 1.0f, 0.0f) },   // 四角形の頂点（右下）
		{ XMFLOAT3(-5.0f, -5.0f, 0.0f),XMFLOAT3(0.0f, 0.0f, 1.0f),XMFLOAT3(0.0f, 1.0f, 0.0f) },   // 四角形の頂点（左下）
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
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	//インデックス情報
	int index[] = { 0,1,2,0,2,3 };

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);


	//テクスチャ
	pTexture_ = new Texture;
	pTexture_->Load(fileName_.c_str());

	return S_OK;
}

//初期化
void Signboard::Initialize()
{
	//画像ロードポリゴン作成
	Load();

	//画像を反転させる
	transform_.rotate_.y += ROTATION_ANGLE_Y;
}

//描画
void Signboard::Draw()
{
	//シェーダをセット
	Direct3D::SetShader(Direct3D::SHADER_SIGNBOARD);
	Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

	XMMATRIX matWorld;
	XMMATRIX matTrans = XMMatrixTranslation(transform_.position_.x, transform_.position_.y, transform_.position_.z);
	XMMATRIX matRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)) * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)) * XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
	XMMATRIX matScale = XMMatrixScaling(transform_.scale_.x, transform_.scale_.y, 1.0f);

	//もしカメラの方向けるなら
	if(isLookCamera_)
		matWorld = matScale * Camera::GetBillboardMatrix() * matTrans;
	else
		matWorld = matScale * matRotate * matTrans;

	// パラメータの受け渡し
	CONSTANT_BUFFER cb;
	cb.worldVewProj = XMMatrixTranspose(matWorld * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());						// リソースへ送る値をセット
	cb.world = XMMatrixTranspose(matWorld);

	//もしカメラの方向けるなら
	if (isLookCamera_)
		cb.normalTrans = XMMatrixTranspose(Camera::GetBillboardMatrix() * XMMatrixInverse(nullptr, Camera::GetBillboardMatrix()));
	else
		cb.normalTrans = XMMatrixTranspose(matRotate * XMMatrixInverse(nullptr, matRotate));
	cb.lightDirection = Light::GetDirection();
	cb.cameraPosition = XMFLOAT4(Camera::GetPosition().x, Camera::GetPosition().y, Camera::GetPosition().z, 0);
	cb.lightPosition = Light::GetPosition(0);

	for (int i = 0; i < LIGHT_TOTAL_NUM; i++)
	{
		cb.pos[i] = Light::GetPosition(i);
		cb.intensity[i] = XMFLOAT4(Light::GetIntensity(i), Light::GetIntensity(i), Light::GetIntensity(i), Light::GetIntensity(i));
	}

	//もしカメラの方を向くなら
	if (GetObjectName() == "LookCamSignboard")
		cb.isBrightness = 10;
	else
		cb.isBrightness = ZERO;

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// リソースへ値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	//今から描画する頂点情報をシェーダに伝える
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//使用するコンスタントバッファをシェーダに伝える
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	Direct3D::pContext_->DrawIndexed(6, 0, 0);

	//シェーダをセット
	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//解放
void Signboard::Release()
{
}
