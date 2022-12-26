#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//更新
void EnemyRotationState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void EnemyRotationState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyRotationState::Enter(Enemy* enemy)
{
}