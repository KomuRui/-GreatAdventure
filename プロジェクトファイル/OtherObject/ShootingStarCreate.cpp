#include "ShootingStarCreate.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/ResourceManager/VFX.h"
#include "../Engine/ResourceManager/Time.h"
#include "ShootingStar.h"

//定数
namespace
{
	static const float GENERATION_TIME = 2.0f;     //生成時間
}

//コンストラクタ
ShootingStarCreate::ShootingStarCreate(GameObject* parent)
	:GameObject(parent, "ShootingStarCreate"), hTime_((int)ZERO)
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
	//タイマーリセット
	Time::Reset(hTime_);

	//流れ星生成
	for(int i = 0; i < 3; i++)
		Instantiate<ShootingStar>(this)->SetPosition(XMFLOAT3((float)Random(-20,90),(float)Random(40,70),(float)Random(-20, 90)));

}