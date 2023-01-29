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

	//Playerが視角内,指定距離内にいるかどうか調べる
	void PlayerNearWithIsCheck() override {};

	//ノックバックして死亡
	void KnockBackDie() override;

	//死亡
	void Die() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;

};

