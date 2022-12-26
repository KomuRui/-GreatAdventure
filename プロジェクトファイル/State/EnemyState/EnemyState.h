#pragma once
#include "EnemyState.h"

//前定義
class Enemy;

//状態の基底クラス
class EnemyState
{
public:

	/// <summary>
	/// 2D用更新
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void Update2D(Enemy* enemy) {};

	/// <summary>
	/// 3D用更新
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void Update3D(Enemy* enemy) {};

	/// <summary>
	/// 入力によって状態変化する
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void HandleInput(Enemy* enemy) {};

	/// <summary>
	/// 状態変化したとき一回だけ呼ばれる関数
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void Enter(Enemy* enemy) {};
};


//状態のリスト
namespace EnemyStateList
{
	EnemyState* GetEnemyWaitState();      //待機状態のインスタンス返す
	EnemyState* GetEnemyMoveState();      //移動状態のインスタンス返す
	EnemyState* GetEnemyRotationState();  //回転状態のインスタンス返す
	EnemyState* GetEnemyDieState();	      //死亡状態のインスタンス返す
	EnemyState* GetEnemyKnockBackState(); //ノックバック状態のインスタンス返す
};
