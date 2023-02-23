#include "WalkingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"

//更新
void WalkingState::Update2D(PlayerBase* player)
{
	HandleInput(player);
}

//3D用更新
void WalkingState::Update3D(PlayerBase* player)
{
}

//入力によって状態変化する
void WalkingState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void WalkingState::Enter(PlayerBase* player)
{
}