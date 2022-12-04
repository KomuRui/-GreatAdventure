#include "RunningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//更新
void RunningState::Update()
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
		GameManager::GetpPlayer()->pState_ = PlayerState::jumping_;
		GameManager::GetpPlayer()->pState_->Enter();
	}

	//回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		GameManager::GetpPlayer()->pState_ = PlayerState::rotationning_;
		GameManager::GetpPlayer()->pState_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void RunningState::Enter()
{
}