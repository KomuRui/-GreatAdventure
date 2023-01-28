#pragma once
#include "PigEnemy.h"

/// <summary>
/// ミニゲーム用の豚の敵
/// </summary>
class MiniGamePigEnemy : public PigEnemy
{

public:

	//コンストラクタ
	MiniGamePigEnemy(GameObject* parent);


	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一度だけ呼ばれる関数
	void ChildPigEnemyStartUpdate() override;

	//更新
	void ChildPigEnemyUpdate() override;

};

