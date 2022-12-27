#include "TitleModel.h"
#include "../Engine/Model.h"

//定数
namespace
{
	static const XMVECTOR MIN_SCALE = { 0.2f,0.2f,1.0f };    //最低拡大率
	static const XMVECTOR MAX_SCALE = { 0.25f,0.25f,1.0f };  //最高拡大率
	static const float INTERPOLATION_FACTOR = 0.03f;      //補間係数
	static const float CHANGE_TARGET_DISTANCE = 0.01f;    //ターゲット変更するときの距離
}

//コンストラクタ
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1), beforeScale_(XMVectorSet(ZERO, ZERO, ZERO, ZERO)), targetScale_(XMVectorSet(0, 0, 0, 0)),
	pSceneChabgeEffect_(nullptr)
{
}

//初期化
void TitleModel::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/Title/Model/TitleModel.fbx");
	assert(hModel_ >= ZERO);


	///////////////エフェクト設定///////////////////

   //エフェクト出すために必要なクラス
	pSceneChabgeEffect_ = Instantiate<Particle>(this);
}

//更新の前に一回呼ばれる関数
void TitleModel::StartUpdate()
{
	//補間する前の拡大率保存
	ARGUMENT_INITIALIZE(beforeScale_, MIN_SCALE);

	//次の目標とする拡大率の保存
	ARGUMENT_INITIALIZE(targetScale_, MAX_SCALE);
}

//更新
void TitleModel::Update()
{
	//拡大率を補間しながら変えていく
	XMStoreFloat3(&transform_.scale_,XMVectorLerp(XMLoadFloat3(&transform_.scale_), targetScale_, INTERPOLATION_FACTOR));

	//距離が0.01より短いのなら
	if (RangeCalculation(transform_.scale_, VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
	{
		//ターゲット交換
		std::swap(beforeScale_, targetScale_);
	}
}

//描画
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void TitleModel::Release()
{
}

//シーン変更エフェクト
void TitleModel::SceneChangeEffect()
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 20;
	data.lifeTime = 150;
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.05f;
	data.speedErr = 0.8;
	data.size = XMFLOAT2(5, 5);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(-0.03, -0.03, 0, -1.0 / 50);
	pSceneChabgeEffect_->Start(data);
}