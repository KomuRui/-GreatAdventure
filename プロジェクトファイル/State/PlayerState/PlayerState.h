#pragma once
#include "../../Engine/Global.h"
#include "../../Engine/Input.h"

class Player;

//状態の基底クラス
class PlayerState
{
public:

	//2D用更新
	virtual void Update2D(Player* player) = 0;

	//3D用更新
	virtual void Update3D(Player* player) = 0;

	//入力によって状態変化する
	virtual void HandleInput(Player* player) = 0;

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter(Player* player) = 0;

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="nowState">現在の状態</param>
	/// <param name="state">変化したい状態</param>
	void ChangeState(PlayerState* nowState,PlayerState* state);
};
