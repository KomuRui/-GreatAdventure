#pragma once
#include "PlayerState.h"

class PlayerBase;

/// <summary>
/// 回転状態
/// </summary>
class RotationningState : public PlayerState
{
	int rotationCount_; //何Fps回転しているか

public:

	//更新
	void Update2D(PlayerBase* player) override;

	//3D用更新
	void Update3D(PlayerBase* player) override;

	//ミニゲーム用更新
	void UpdateMiniGame(PlayerBase* player) override {};

	//入力によって状態変化する
	void HandleInput(PlayerBase* player) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(PlayerBase* player) override;
};

