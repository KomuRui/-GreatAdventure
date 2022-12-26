#include "EnemyKnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//更新
void EnemyKnockBackState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void EnemyKnockBackState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyKnockBackState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyKnockBackState::Enter(Enemy* enemy)
{
}