#pragma once
#include "../Mob.h"

/// <summary>
/// ミニゲームの登場するギミックの回る円
/// </summary>
class TurnCircle : public Mob
{

public:

	//コンストラクタ
	TurnCircle(GameObject * parent);

	/////////////////////オーバーライドする関数//////////////////////

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;

};

