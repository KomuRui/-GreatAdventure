#include "EnemyStateManager.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Enemy/Enemy.h"

//各static変数の初期化
EnemyDieState* EnemyStateManager::EnemyDie_ = new EnemyDieState;
EnemyKnockBackState* EnemyStateManager::EnemyKnockBack_ = new EnemyKnockBackState;
EnemyMoveState* EnemyStateManager::EnemyMove_ = new EnemyMoveState;
EnemyRotationState* EnemyStateManager::EnemyRotation_ = new EnemyRotationState;
EnemyWaitState* EnemyStateManager::EnemyWait_ = new EnemyWaitState;

//コンストラクタ
EnemyStateManager::EnemyStateManager()
{
}

//更新
void EnemyStateManager::Update2D(Enemy* enemy)
{
    //現在の状態の更新を呼ぶ
    //EnemyState_->Update2D(enemy);
}

//3D用更新
void EnemyStateManager::Update3D(Enemy* enemy)
{
    //現在の状態の更新を呼ぶ
    //EnemyState_->Update3D(enemy);
}

//入力によって状態変化する
void EnemyStateManager::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyStateManager::Enter(Enemy* enemy)
{
}
