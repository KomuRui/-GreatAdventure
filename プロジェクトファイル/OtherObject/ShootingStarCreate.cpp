#include "ShootingStarCreate.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Engine/ResourceManager/Time.h"

//定数
namespace
{
	static const int GENERATION_TIME = 2.0f;     //生成時間
	static const float GENERATION_POS_Y = 20.0f; //生成ポジションY
}

//コンストラクタ
ShootingStarCreate::ShootingStarCreate(GameObject* parent)
	:GameObject(parent, "ShootingStarCreate"), hTime_(ZERO)
{
}

//初期化
void ShootingStarCreate::Initialize()
{
	//タイマー追加
	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	//タイマースタート
	Time::UnLock(hTime_);
}

//更新
void ShootingStarCreate::Update()
{
	//生成時間が来たら生成
	if (Time::GetTimei(hTime_) >= GENERATION_TIME) Generation();
}

//生成
void ShootingStarCreate::Generation()
{

}