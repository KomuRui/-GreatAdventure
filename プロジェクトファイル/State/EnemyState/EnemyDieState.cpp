#include "EnemyDieState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//更新
void EnemyDieState::Update2D(Enemy* enemy)
{
	//入力処理
	HandleInput(enemy);
}

//3D用更新
void EnemyDieState::Update3D(Enemy* enemy)
{
	//死亡
	enemy->Die();
	
	//入力処理
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyDieState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyDieState::Enter(Enemy* enemy)
{
}