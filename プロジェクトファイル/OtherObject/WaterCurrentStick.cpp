#include "WaterCurrentStick.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//コンストラクタ
WaterCurrentStick::WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_), front_(STRAIGHT_VECTOR),hEffect_(ZERO)
{
}

//初期化
void WaterCurrentStick::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load(filePath_);
	assert(hModel_ >= ZERO);

	//前ベクトル更新
	front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y))));

	//水流のエフェクト表示
	hEffect_ = OtherEffectManager::WaterCurrentEffect(transform_.position_,VectorToFloat3(front_));
}

//更新
void WaterCurrentStick::Update()
{
	////前ベクトル更新
	//front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(10))));

	////エフェクトの方向変える
	//VFX::GetEmitter(hEffect_)->data.direction = VectorToFloat3(front_);
}

//描画
void WaterCurrentStick::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void WaterCurrentStick::Release()
{
}
