#include "EnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//更新
void EnemyMoveState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void EnemyMoveState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyMoveState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyMoveState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 19 + 12) * 10;
	ZERO_INITIALIZE(stateCount_);
}