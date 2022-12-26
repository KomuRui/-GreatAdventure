#include "PigEnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//更新
void PigEnemyMoveState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void PigEnemyMoveState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void PigEnemyMoveState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyMoveState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 19 + 12) * 10;
	ZERO_INITIALIZE(stateCount_);
}