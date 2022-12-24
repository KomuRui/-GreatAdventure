#include "RunningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//更新
void RunningState::Update2D()
{
	HandleInput();
}

//3D用更新
void RunningState::Update3D()
{
	HandleInput();
}

//入力によって状態変化する
void RunningState::HandleInput()
{
	//ジャンプ状態に変更
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerState::playerState_ = PlayerState::playerJumping_;
		PlayerState::playerState_->Enter();
	}

	//回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerState::playerState_ = PlayerState::playerRotationning_;
		PlayerState::playerState_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void RunningState::Enter()
{
}