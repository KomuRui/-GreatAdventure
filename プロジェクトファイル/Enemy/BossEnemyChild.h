#pragma once
#include "Enemy.h"

/// <summary>
/// ボスの子供のクラス
/// </summary>
class BossEnemyChild : public Enemy
{
private:

	///////////////ノックバック///////////////////

	//ノックバックの方向と距離
	XMVECTOR knockBackDir_;

	//空飛ぶときの元となる上ベクトル
	XMVECTOR vFly_;

	//元となるフライベクトルを保存しておく
	XMVECTOR keepFly_;

	//ノックバックしたかどうか
	bool isKnockBack_;

	///////////////その他///////////////////

	//コライダー
	SphereCollider* collision;


public:

	//コンストラクタ
	BossEnemyChild(GameObject* parent, std::string modelPath, std::string name);

	//コンストラクタ
	BossEnemyChild(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	//ノックバックして死亡
	void KnockBackDie() override;

	//死亡
	void Die() override;

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;

	//////////////////////////////関数///////////////////////////////

	/// <summary>
	/// 継承先用の更新の前に一度だけ呼ばれる関数
	/// </summary>
	virtual void ChildBossEnemyChildStartUpdate() {};

	/// <summary>
	/// 継承先用の更新
	/// </summary>
	virtual void ChildBossEnemyChildUpdate() {};

};