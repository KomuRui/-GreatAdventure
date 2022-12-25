#include "PigEnemyState.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"

//各static変数の初期化
PigEnemyDieState* PigEnemyState::pigEnemyDie_ = new PigEnemyDieState;
PigEnemyKnockBackState* PigEnemyState::pigEnemyKnockBack_ = new PigEnemyKnockBackState;
PigEnemyMoveState* PigEnemyState::pigEnemyMove_ = new PigEnemyMoveState;
PigEnemyRotationState* PigEnemyState::pigEnemyRotation_ = new PigEnemyRotationState;
PigEnemyWaitState* PigEnemyState::pigEnemyWait_ = new PigEnemyWaitState;
State* PigEnemyState::pigEnemyState_ = pigEnemyWait_;

//コンストラクタ
PigEnemyState::PigEnemyState()
{
}

//更新
void PigEnemyState::Update2D()
{
    //現在の状態の更新を呼ぶ
    pigEnemyState_->Update2D();
}

//3D用更新
void PigEnemyState::Update3D()
{
    //現在の状態の更新を呼ぶ
    pigEnemyState_->Update3D();
}

//入力によって状態変化する
void PigEnemyState::HandleInput()
{
}

//状態変化したとき一回だけ呼ばれる関数
void PigEnemyState::Enter()
{
}
