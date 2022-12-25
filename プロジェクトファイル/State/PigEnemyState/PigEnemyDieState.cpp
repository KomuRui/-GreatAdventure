#include "PigEnemyDieState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyState.h"

//更新
void PigEnemyDieState::Update2D()
{
	HandleInput();
}

//3D用更新
void PigEnemyDieState::Update3D()
{
	HandleInput();
}

//入力によって状態変化する
void PigEnemyDieState::HandleInput()
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyDieState::Enter()
{
}