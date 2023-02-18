#pragma once
#include "Enemy.h"

/// <summary>
/// 豚の敵クラス
/// </summary>
class PigEnemy : public Enemy
{
protected:


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
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);
	
	//コンストラクタ
	PigEnemy(GameObject* parent, std::string name);

	/////////////////////オーバーライドする関数//////////////////////
	
	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	//ノックバックして死亡
	virtual void KnockBackDie() override;

	//死亡
	virtual void Die() override;

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override;

	//////////////////////////////関数///////////////////////////////

	/// <summary>
	/// 継承先用の更新の前に一度だけ呼ばれる関数
	/// </summary>
	virtual void ChildPigEnemyStartUpdate() {};

	/// <summary>
	/// 継承先用の更新
	/// </summary>
	virtual void ChildPigEnemyUpdate() {};

	/// <summary>
	/// Playerが自身の上にいるかどうか
	/// </summary>
	/// <returns>trueならいる,falseならいない</returns>
	bool IsPlayerTop();

	
};