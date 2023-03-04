#pragma once
#include "Enemy.h"

/// <summary>
/// 最後のボス
/// </summary>
class BossEnemy : public Enemy
{
	//ボスの体力
	int hp_;

	///////////////ノックバック///////////////////

	//ノックバックの方向と距離
	XMVECTOR knockBackDir_;

	//空飛ぶときの元となる上ベクトル
	XMVECTOR vFly_;

	//元となるフライベクトルを保存しておく
	XMVECTOR keepFly_;

	//ノックバックしたかどうか
	bool isKnockBack_;


public:

	//コンストラクタ
	BossEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	//Playerが視角内、指定距離内にいる時の処理
	void PlayerWithIf() override;

	//Playerが視角内、指定距離内にいない時の処理
	void NotPlayerWithIf() override;

	//Playerが視角内,指定距離内にいるかどうか調べる
	void PlayerNearWithIsCheck() override {};

	//常に探索範囲内にいるように
	bool IsInSearchRange() override { return true; }

	//ノックバック
	void KnockBackDie() override;

	//死亡
	void Die() override;

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;
};

