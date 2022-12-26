#include "PigEnemyDieState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//更新
void PigEnemyDieState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void PigEnemyDieState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void PigEnemyDieState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyDieState::Enter(Enemy* enemy)
{
}