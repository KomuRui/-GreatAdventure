#include "EnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "../../Enemy/Enemy.h"

//更新
void EnemyMoveState::Update2D(Enemy* enemy)
{
	//入力処理
	HandleInput(enemy);
}

//3D用更新
void EnemyMoveState::Update3D(Enemy* enemy)
{
    //移動
	enemy->Move();

     //状態が状態変化の時間より大きくなったら
    if (stateCount_ > operationTime_)
    {
        //0に初期化
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        //状態を回転に設定
        enemy->ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //アニメーション停止
        Model::SetAnimFlag(enemy->GetModelNumber(), false);
    }

    //状態秒数増やす
    stateCount_++;

	//入力処理
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