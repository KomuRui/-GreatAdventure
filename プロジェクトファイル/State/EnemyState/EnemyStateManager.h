#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "EnemyState.h"
#include "EnemyStateManager.h"
#include "EnemyDieState.h"
#include "EnemyKnockBackState.h"
#include "EnemyMoveState.h"
#include "EnemyRotationState.h"
#include "EnemyWaitState.h"

//前定義
class Enemy;

/// <summary>
/// PigEnemyの状態を管理
/// </summary>
class EnemyStateManager : public EnemyState
{

public:

	//各状態変数
	static EnemyDieState* EnemyDie_;             //死亡
	static EnemyKnockBackState* EnemyKnockBack_; //ノックバック
	static EnemyMoveState* EnemyMove_;		    //移動
	static EnemyRotationState* EnemyRotation_;   //回転
	static EnemyWaitState* EnemyWait_;		    //待機

	//コンストラクタ
	EnemyStateManager();

	//2D用更新
	void Update2D(Enemy* enemy) override;

	//3D用更新
	void Update3D(Enemy* enemy) override;

	//入力によって状態変化する
	void HandleInput(Enemy* enemy) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(Enemy* enemy) override;

};



