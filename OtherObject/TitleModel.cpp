#include "TitleModel.h"
#include "../Engine/Model.h"

//コンストラクタ
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1), beforeScale_(XMVectorSet(0,0,0,0))
{
}

//初期化
void TitleModel::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load("Stage/Title/Model/TitleModel.fbx");
	assert(hModel_ >= ZERO);

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
	if (Transform::RangeCalculation(transform_.scale_, Transform::VectorToFloat3(targetScale_)) < CHANGE_TARGET_DISTANCE)
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
