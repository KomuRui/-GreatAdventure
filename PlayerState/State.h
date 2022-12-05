#pragma once
#include "../Engine/Input.h"

//Playerの状態の基底クラス
class State
{
public:

	//2D用更新
	virtual void Update2D() = 0;

	//3D用更新
	virtual void Update3D() = 0;

	//入力によって状態変化する
	virtual void HandleInput() = 0;

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter() = 0;

};
