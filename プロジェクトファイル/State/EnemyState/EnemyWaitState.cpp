#include "EnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//更新
void EnemyWaitState::Update2D(Enemy* enemy)
{
	//入力処理
	HandleInput(enemy);
}

//3D用更新
void EnemyWaitState::Update3D(Enemy* enemy)
{
	//待機
	enemy->Wait();

	//状態秒数増やす
	enemy->SetStateCount(enemy->GetStateCount()+ 1);

	//入力処理
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyWaitState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyWaitState::Enter(Enemy* enemy)
{
	enemy->SetOperationTime((rand() % 13 + 6) * 10);
	enemy->SetStateCount(ZERO);
}