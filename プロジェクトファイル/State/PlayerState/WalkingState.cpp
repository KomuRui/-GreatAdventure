#include "WalkingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"

//更新
void WalkingState::Update2D(Player* player)
{
	HandleInput(player);
}

//3D用更新
void WalkingState::Update3D(Player* player)
{
}

//入力によって状態変化する
void WalkingState::HandleInput(Player* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void WalkingState::Enter(Player* player)
{
}