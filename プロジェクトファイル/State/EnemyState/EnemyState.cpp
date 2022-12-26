#include "EnemyState.h"
#include "EnemyDieState.h"
#include "EnemyKnockBackState.h"
#include "EnemyMoveState.h"
#include "EnemyRotationState.h"
#include "EnemyWaitState.h"

//状態のリスト
namespace EnemyStateList
{
	//各状態変数
	static EnemyDieState* EnemyDie_ = new EnemyDieState;                   //死亡
	static EnemyKnockBackState* EnemyKnockBack_ = new EnemyKnockBackState; //ノックバック
	static EnemyMoveState* EnemyMove_ = new EnemyMoveState;		           //移動
	static EnemyRotationState* EnemyRotation_ = new EnemyRotationState;    //回転
	static EnemyWaitState* EnemyWait_ = new EnemyWaitState;		           //待機

	EnemyState* GetEnemyWaitState() { return EnemyWait_; }			 //待機状態のインスタンス返す
	EnemyState* GetEnemyMoveState() { return EnemyMove_; }			 //移動状態のインスタンス返す
	EnemyState* GetEnemyRotationState() { return EnemyRotation_; }	 //回転状態のインスタンス返す
	EnemyState* GetEnemyDieState() { return EnemyDie_; }			 //死亡状態のインスタンス返す
	EnemyState* GetEnemyKnockBackState() { return EnemyKnockBack_; };//ノックバック状態のインスタンス返す
}

