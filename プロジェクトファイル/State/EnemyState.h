#pragma once
#include "../Engine/Input.h"
#include "../Engine/Global.h"

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
	virtual void Update2D(Enemy* enemy) = 0;

	/// <summary>
	/// 3D用更新
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void Update3D(Enemy* enemy) = 0;

	/// <summary>
	/// 入力によって状態変化する
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void HandleInput(Enemy* enemy) = 0;

	/// <summary>
	/// 状態変化したとき一回だけ呼ばれる関数
	/// </summary>
	/// <param name="enemy">状態を使ってる敵のポインタ</param>
	virtual void Enter(Enemy* enemy) = 0;
};
