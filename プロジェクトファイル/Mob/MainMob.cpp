#include "MainMob.h"
#include "../Engine/ImGuiSet.h"

//定数
namespace
{
	////////////////////////////アニメーション////////////////////////////

	static const int START_FRAME = 0;	  //開始フレーム
	static const int END_FRAME = 120;     //終了フレーム
	static const float ANIM_SPEED = 1.0f; //アニメーションの再生速度

	////////////////////////////その他////////////////////////////

	static const float PLAYER_LOOK_DISTANCE = 8; //Playerの方を向く時の距離
}

//コンストラクタ
MainMob::MainMob(GameObject* parent, std::string modelPath, std::string name) 
	:Mob(parent, modelPath, name),isAnim_(true),toPlayer_(XMMatrixIdentity()), isLookPlayer_(false)
{}

//更新の前に一度だけ呼ばれる
void MainMob::ChildStartUpdate()
{
	//もしアニメーションするなら
	if (isAnim_)
	{
		//アニメーション
		Model::SetAnimFrame(hModel_, START_FRAME, END_FRAME, ANIM_SPEED);
		Model::SetAnimFlag(hModel_, true);
	}
}

//更新
void MainMob::ChildUpdate()
{
	//もしアニメーションしてないならPlayerの方を向く
	if (!isAnim_)
		LookPlayer();
}

//Playerの方を向く
void MainMob::LookPlayer()
{
	//もし一回でもPlayerの方向いていたら
	if(isLookPlayer_)
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

	//Playerとの距離が8以内ならPlayerの方を向く
	if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < PLAYER_LOOK_DISTANCE)
	{
		toPlayer_ = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_), up_);
		transform_.mmRotate_ = XMMatrixInverse(nullptr, toPlayer_);

		ARGUMENT_INITIALIZE(isLookPlayer_, true);
	}
}