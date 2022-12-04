#include "StandingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//更新
void StandingState::Update()
{
	HandleInput();
}

//入力によって状態変化する
void StandingState::HandleInput()
{
	//ジャンプ状態に変更
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		GameManager::GetpPlayer()->pState_ = PlayerState::jumping_;
		GameManager::GetpPlayer()->pState_->Enter();
	}

	//走る状態に変更
	if (Input::GetPadTrrigerL())
	{
		//状態変更
		GameManager::GetpPlayer()->pState_ = PlayerState::running_;
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
void StandingState::Enter()
{
}
