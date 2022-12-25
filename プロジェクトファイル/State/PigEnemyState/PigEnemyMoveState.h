#pragma once
#include "../State.h"

/// <summary>
/// 移動状態のクラス
/// </summary>
class PigEnemyMoveState : public State
{
	int operationTime_;     //次の状態に変わるまでの時間
	int stateCount_;        //その状態になってからどのくらいの秒数たったか

public:

	//2D用更新
	void Update2D() override;

	//3D用更新
	void Update3D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;
};