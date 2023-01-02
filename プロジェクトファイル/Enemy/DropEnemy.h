#pragma once
#include "Enemy.h"
#include "../Engine/Particle.h"

/// <summary>
/// 水玉みたいな敵のクラス
/// </summary>
class DropEnemy : public Enemy
{
	///////////////エフェクト///////////////////

	//エフェクトの番号
	int effectNum_;

	///////////////モデル///////////////////

	//頭のモデル
	int hHedModel_; 

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

	//タイムメソッドで呼ばれるメソッドを切り替えているかどうか
	bool isTimeMethodChange_;

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

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//何かのオブジェクトに当たった時に呼ばれる関数
	void OnCollision(GameObject* pTarget) override;
};

