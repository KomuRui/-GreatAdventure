#pragma once
#include "State.h"

class JumpingState : public State
{
	XMVECTOR vJamp_;        //ジャンプするときの元となる上ベクトル
	XMVECTOR keepJamp_;     //もととなるジャンプベクトルを保存しておく

public:

	//更新
	void Update() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;
};

