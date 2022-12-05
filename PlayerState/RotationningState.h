#pragma once
#include "State.h"

class RotationningState : public State
{
	int rotationCount_; //何Fps回転しているか

public:

	//更新
	void Update2D() override;

	//3D用更新
	void Update3D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;
};

