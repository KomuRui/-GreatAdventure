#pragma once
#include "Enemy.h"

class DropEnemy : public Enemy
{
	//頭のモデル
	int hHedModel_; 

	//ノックバックの方向と距離
	XMVECTOR knockBackDir_;

	//ノックバックしたかどうか
	bool knockBackFlag_;

public:

	//コンストラクタ
	DropEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	//描画
	void EnemyChildDraw() override;

	//Playerが視角内、指定距離内にいる時の処理
	void PlayerWithIf() override;

	//Playerが視角内、指定距離内にいない時の処理
	void NotPlayerWithIf() override;

	//ノックバックして死亡
	void KnockBackDie() override;

	//死亡
	void Die() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;
};

