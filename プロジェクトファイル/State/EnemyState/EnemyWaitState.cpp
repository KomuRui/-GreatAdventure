#include "EnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
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

	//状態が状態変化の時間より大きくなったら
	if (stateCount_ > operationTime_)
	{
		//0に初期化
		ZERO_INITIALIZE(operationTime_);

		//状態をMoveに変更
		enemy->ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
	}

	//状態秒数増やす
	stateCount_++;

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
	operationTime_ = (rand() % 13 + 6) * 10;
	ZERO_INITIALIZE(stateCount_);
}