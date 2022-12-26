#include "PigEnemyStateManager.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"

//各static変数の初期化
PigEnemyDieState* PigEnemyStateManager::pigEnemyDie_ = new PigEnemyDieState;
PigEnemyKnockBackState* PigEnemyStateManager::pigEnemyKnockBack_ = new PigEnemyKnockBackState;
PigEnemyMoveState* PigEnemyStateManager::pigEnemyMove_ = new PigEnemyMoveState;
PigEnemyRotationState* PigEnemyStateManager::pigEnemyRotation_ = new PigEnemyRotationState;
PigEnemyWaitState* PigEnemyStateManager::pigEnemyWait_ = new PigEnemyWaitState;
EnemyState* PigEnemyStateManager::pigEnemyState_ = pigEnemyWait_;

//コンストラクタ
PigEnemyStateManager::PigEnemyStateManager()
{
}

//更新
void PigEnemyStateManager::Update2D(Enemy* enemy)
{
    //現在の状態の更新を呼ぶ
    pigEnemyState_->Update2D(enemy);
}

//3D用更新
void PigEnemyStateManager::Update3D(Enemy* enemy)
{
    //現在の状態の更新を呼ぶ
    pigEnemyState_->Update3D(enemy);
}

//入力によって状態変化する
void PigEnemyStateManager::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyStateManager::Enter(Enemy* enemy)
{
}
