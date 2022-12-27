#include "RunningState.h"
#include "../../Engine/Input.h"
#include "PlayerStateManager.h"

//更新
void RunningState::Update2D(Player* player)
{
	HandleInput(player);
}

//3D用更新
void RunningState::Update3D(Player* player)
{
	HandleInput(player);
}

//入力によって状態変化する
void RunningState::HandleInput(Player* player)
{
	//ジャンプ状態に変更
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}

	//回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//状態変化したとき一回だけ呼ばれる関数
void RunningState::Enter(Player* player)
{
}