#include "JumpingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Global.h"
#include "PlayerState.h"

//更新
void JumpingState::Update()
{
	//ジャンプするベクトルがプラスだったら
	if (XMVectorGetY(vJamp_) >= 0)
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60);
	}

	HandleInput();
}

//入力によって状態変化する
void JumpingState::HandleInput()
{
	//ジャンプ回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		GameManager::GetpPlayer()->pState_ = PlayerState::jumpRotationning_;
		GameManager::GetpPlayer()->pState_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void JumpingState::Enter()
{
	//ジャンプのベクトル・フラグ初期化
	ARGUMENT_INITIALIZE(vJamp_, (XMVectorSet(0, 1, 0, 0)) / 2);
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//先に呼んでおく
	Update();
}