#pragma once
#include "../Engine/Input.h"

//Playerの状態の基底クラス
class PlayerState
{

public:

	//更新
	virtual void Update() = 0;

	//入力によって状態変化する
	virtual void HandleInput() = 0;

};
