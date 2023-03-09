#include "WaterCurrentStick.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//定数
namespace
{
	static const int ROTATION_ANGLE = 10; //回転角度

	/// <summary>
	/// 関数のポインタ配列
	/// </summary>
	static void (WaterCurrentStick::* InstantiateArray[])() = { &WaterCurrentStick::Normal, &WaterCurrentStick::Rotation };

}

//コンストラクタ
WaterCurrentStick::WaterCurrentStick(GameObject* parent, std::string modelFilePath_, std::string name)
	:GameObject(parent, name), hModel_(-1), filePath_(modelFilePath_), front_(STRAIGHT_VECTOR),hEffect_(ZERO),
	type_(WaterCurrentStickType::NORMAL)
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
	//型によって呼ぶ関数を分ける
	(this->*InstantiateArray[static_cast<int>(type_)])();
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

//回転
void WaterCurrentStick::Rotation()
{
	//前ベクトル更新
	front_ = XMVector3Normalize(XMVector3TransformCoord(front_, XMMatrixRotationY(XMConvertToRadians(ROTATION_ANGLE))));

	//エフェクトの方向変える
	VFX::GetEmitter(hEffect_)->data.direction = VectorToFloat3(front_);
}