#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Input.h"

class PlayerBase;

/// <summary>
/// Playerの状態の基底クラス
/// </summary>
class PlayerState
{
public:

	/// <summary>
	/// 2D用更新
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Update2D(PlayerBase* player) {};

	/// <summary>
	/// 3D用更新
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Update3D(PlayerBase* player) {};

	/// <summary>
	/// ミニゲーム用更新
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void UpdateMiniGame(PlayerBase* player) {};

	/// <summary>
	/// 入力によって状態を変化する
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void HandleInput(PlayerBase* player) {};

	/// <summary>
	/// 状態変化したときに一度だけ呼ばれる関数
	/// </summary>
	/// <param name="player">Playerのポインタ</param>
	virtual void Enter(PlayerBase* player) {};

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="nowState">現在の状態</param>
	/// <param name="state">変化したい状態</param>
	void ChangeState(PlayerState* nowState,PlayerState* state);
};
