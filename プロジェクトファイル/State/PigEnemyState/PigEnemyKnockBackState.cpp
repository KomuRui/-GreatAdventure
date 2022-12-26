#include "PigEnemyKnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//更新
void PigEnemyKnockBackState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void PigEnemyKnockBackState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void PigEnemyKnockBackState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyKnockBackState::Enter(Enemy* enemy)
{
}