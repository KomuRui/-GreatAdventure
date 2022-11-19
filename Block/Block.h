#pragma once
#include "../Mob.h"

class Block : public Mob
{
protected:

	XMFLOAT3 hitMovePos_; //Playerと衝突した場合のブロックのポジション
	bool     isHit_;      //Playerと当たっているか

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

	//当たっているか
	void SetIsHit(bool flag) { isHit_ = flag; }

	///////////////////継承先用関数/////////////////////

	//継承先ごとにUpdateでの動き方を変える
	virtual void BlockChildUpdate() {};

	//継承先用の初期化
	virtual void BlockChildInitialize() {};

	//継承先用の描画
	virtual void BlockChildDraw() {};

	//継承先用のスタートアップデート
	virtual void BlockChildStartUpdate() {};

	//Playerが下から当たった時の挙動
	virtual void HitToLowerPlayer();

	//継承先用のコライダー当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override {};

	//継承先用の指定した時間で呼ばれるメソッド
	virtual void TimeMethod() override {};

};

