#pragma once
#include  "EnemyState.h"

//前定義
class Enemy;

/// <summary>
/// 回転状態のクラス
/// </summary>
class EnemyRotationState : public EnemyState
{
	int rotationAngle_;     //回転角度
	int rotationSign_;      //回転符号
	float rotationTotal_;   //どのくらい回転したか

public:

	//2D用更新
	void Update2D(Enemy* enemy) override;

	//3D用更新
	void Update3D(Enemy* enemy) override;

	//入力によって状態変化する
	void HandleInput(Enemy* enemy) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(Enemy* enemy) override;
};