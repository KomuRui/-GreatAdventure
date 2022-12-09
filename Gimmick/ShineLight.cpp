#include "ShineLight.h"
#include "../Engine/Light.h"
#include "../Engine/Model.h"

//コンストラクタ
ShineLight::ShineLight(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), shineFlag_(false),lightNum_(0),num_(1)
{
}

//更新の前に一回だけ呼ばれる更新
void ShineLight::ChildStartUpdate()
{
	//レイの判定にいれたいのでtrueにしておく
	Model::SetRayFlag(hModel_, true);
}

//更新
void ShineLight::ChildUpdate()
{
	//プレイヤーとの距離が反応距離より小さいかつ光っていないのなら
	if (Transform::RangeCalculation(GameManager::GetpPlayer()->GetPosition(), transform_.position_) < REACTION_DISTANCE && !shineFlag_)
	{
		//ライト設置
		XMFLOAT4 lightPos = { transform_.position_.x,transform_.position_.y, transform_.position_.z,ZERO };
		lightNum_ = Light::SetPositionAndIntensity(lightPos, -LIGHT_INTENSITY);

		//光っているように設定
		ARGUMENT_INITIALIZE(shineFlag_, true);
	}

}
