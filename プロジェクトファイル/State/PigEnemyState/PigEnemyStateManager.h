#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../EnemyState.h"
#include "PigEnemyStateManager.h"
#include "PigEnemyDieState.h"
#include "PigEnemyKnockBackState.h"
#include "PigEnemyMoveState.h"
#include "PigEnemyRotationState.h"
#include "PigEnemyWaitState.h"

//前定義
class Enemy;

/// <summary>
/// PigEnemyの状態を管理
/// </summary>
class PigEnemyStateManager : public EnemyState
{

public:

	//状態を示す変数
	static EnemyState* pigEnemyState_;

	//各状態変数
	static PigEnemyDieState* pigEnemyDie_;             //死亡
	static PigEnemyKnockBackState* pigEnemyKnockBack_; //ノックバック
	static PigEnemyMoveState* pigEnemyMove_;		   //移動
	static PigEnemyRotationState* pigEnemyRotation_;   //回転
	static PigEnemyWaitState* pigEnemyWait_;		   //待機

	//コンストラクタ
	PigEnemyStateManager();

	//2D用更新
	void Update2D(Enemy* enemy) override;

	//3D用更新
	void Update3D(Enemy* enemy) override;

	//入力によって状態変化する
	void HandleInput(Enemy* enemy) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(Enemy* enemy) override;

};



