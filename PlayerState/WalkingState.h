#pragma once
#include "State.h"

class WalkingState : public State
{
public:

	//更新
	void Update2D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;
};

