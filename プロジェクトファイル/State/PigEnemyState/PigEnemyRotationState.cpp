#include "PigEnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//更新
void PigEnemyRotationState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void PigEnemyRotationState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//入力によって状態変化する
void PigEnemyRotationState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyRotationState::Enter(Enemy* enemy)
{
}