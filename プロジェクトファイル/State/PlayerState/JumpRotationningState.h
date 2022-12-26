#pragma once
#include "PlayerState.h"

class Player;

class JumpRotationningState : public PlayerState
{
	XMVECTOR vJamp_;        //ジャンプするときの元となる上ベクトル
	XMVECTOR keepJamp_;     //もととなるジャンプベクトルを保存しておく

public:

	//2D用更新
	void Update2D(Player* player) override;

	//3D用更新
	void Update3D(Player* player) override;

	//入力によって状態変化する
	void HandleInput(Player* player) override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter(Player* player) override;
};

