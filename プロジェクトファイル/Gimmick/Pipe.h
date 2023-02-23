#pragma once
#include "../Mob/Mob.h"

/// <summary>
/// ミニゲームに登場するギミックのパイプ
/// </summary>
class Pipe : public Mob
{

public:

	//コンストラクタ
	Pipe(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;
};

