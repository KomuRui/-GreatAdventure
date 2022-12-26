#include "PigEnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//更新
void PigEnemyWaitState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D用更新
void PigEnemyWaitState::Update3D(Enemy* enemy)
{
    //状態時間が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);

        //状態をMoveに変更
        PigEnemyStateManager::pigEnemyState_ = PigEnemyStateManager::pigEnemyMove_;
        PigEnemyStateManager::pigEnemyState_->Enter(enemy);
    }

	HandleInput(enemy);
}

//入力によって状態変化する
void PigEnemyWaitState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyWaitState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 13 + 6) * 10;
	ZERO_INITIALIZE(stateCount_);
}