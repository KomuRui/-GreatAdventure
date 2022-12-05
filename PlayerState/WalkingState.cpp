#include "WalkingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//更新
void WalkingState::Update2D()
{
	HandleInput();
}

//3D用更新
void WalkingState::Update3D()
{
}

//入力によって状態変化する
void WalkingState::HandleInput()
{
}

//状態変化したとき一回だけ呼ばれる関数
void WalkingState::Enter()
{
}