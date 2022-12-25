#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../State.h"
#include "PigEnemyDieState.h"
#include "PigEnemyKnockBackState.h"
#include "PigEnemyMoveState.h"
#include "PigEnemyRotationState.h"
#include "PigEnemyWaitState.h"

//Playerの状態の基底クラス
class PigEnemyState : public State
{
public:

	//状態を示す変数
	static State* pigEnemyState_;

	//各状態変数
	static PigEnemyDieState* pigEnemyDie_;             //死亡
	static PigEnemyKnockBackState* pigEnemyKnockBack_; //ノックバック
	static PigEnemyMoveState* pigEnemyMove_;		   //移動
	static PigEnemyRotationState* pigEnemyRotation_;   //回転
	static PigEnemyWaitState* pigEnemyWait_;		   //待機

	//コンストラクタ
	PigEnemyState();

	//2D用更新
	void Update2D() override;

	//3D用更新
	void Update3D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;

};



