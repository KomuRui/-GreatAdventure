#pragma once
#include "../Mob.h"

/// <summary>
/// ブロックの基底クラス(全てのブロックはこのクラスを継承して作る)
/// </summary>
class Block : public Mob
{
protected:

	XMFLOAT3 hitMovePos_;   //Playerと衝突した場合のブロックのポジション
	XMFLOAT3 initialPos_;   //初期ポジション
	bool     isHit_;        //Playerと当たっているか
	bool     roundTripEnd_; //往復が終わったかどうか

public:
	//コンストラクタ
	Block(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	//更新の前に一回呼ばれる関数
	void ChildStartUpdate() override;

	///////////セッター////////////

	/// <summary>
	/// 当たっているのかをセットする
	/// </summary>
	/// <param name="flag">当たっているならtrue,当たっていないのならfalse</param>
	void SetIsHit(const bool& flag) { isHit_ = flag; }

	///////////////////継承先用関数/////////////////////

	/// <summary>
	/// 継承先ごとにUpdateでの動き方を変える
	/// </summary>
	virtual void BlockChildUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void BlockChildInitialize() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void BlockChildDraw() {};

	/// <summary>
	/// 継承先用のスタートアップデート
	/// </summary>
	virtual void BlockChildStartUpdate() {};

	/// <summary>
	/// Playerが下から当たった時の挙動
	/// </summary>
	virtual void HitToLowerPlayer();

	/// <summary>
	/// 継承先用のPlayerが下から当たった時の挙動
	/// </summary>
	virtual void BlockChildHitToLowerPlayer() {};

	/// <summary>
	/// 継承先用のコライダー当たった時に呼ばれる関数
	/// </summary>
	/// <param name="pTarget">当たった相手のポインタ</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// 継承先用の指定した時間で呼ばれるメソッド
	/// </summary>
	virtual void TimeMethod() override {};

};

