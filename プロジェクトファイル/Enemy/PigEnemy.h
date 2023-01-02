#pragma once
#include "Enemy.h"
#include "../Engine/Particle.h"

/// <summary>
/// 豚の敵クラス
/// </summary>
class PigEnemy : public Enemy
{

	///////////////エフェクト///////////////////

	//エフェクトの番号
	int effectNum_;

	///////////////ノックバック///////////////////

	//ノックバックの方向と距離
	XMVECTOR knockBackDir_;

	//空飛ぶときの元となる上ベクトル
	XMVECTOR vFly_;

	//元となるフライベクトルを保存しておく
	XMVECTOR keepFly_;

	//ノックバックしたかどうか
	bool knockBackFlag_;

public:

	//コンストラクタ
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	/// <summary>
	/// Playerが自身の上にいるかどうか
	/// </summary>
	/// <returns>trueならいる,falseならいない</returns>
	bool IsPlayerTop();

	//ノックバックして死亡
	void KnockBackDie() override;

	//死亡
	void Die() override;

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;
};