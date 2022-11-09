#pragma once
#include "../Mob.h"

//ワープクラス
class Warp : public Mob
{
private:

	//定数
	const float    ROTATION_QUANTITY = 0.02f;        //回転量
	const float    ADDITION_TURNOVERRATE = 0.02f;   //回転率を加算する量
	const float    MAX_TURNOVERRATE = 5.0f;         //最大回転率
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };     //コライダーポジション
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 }; //コライダーサイズ

	//変数
	float    turnoverRate_;  //回転率
	int      status_;        //状態
	XMFLOAT3 playerPos_;     //ワープにPlayerを乗せるときのPlayerのポジションを設定

	//ワープに状態
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

public:

	//コンストラクタ
	Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(Stop)
		, turnoverRate_(1), playerPos_(0, 0, 0)
	{}

	//初期化
	void ChildInitialize() override
	{
		//自身に当たり判定を追加
		BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
		AddCollider(collision);

		//ワープにPlayerを乗せるときのPlayerのポジションを設定
		playerPos_ = { transform_.position_.x,transform_.position_.y - 1.0f,transform_.position_.z };
	}

	//ワープの動き方
	void UpdateMove() override
	{
		//Y軸回転させる
		Angle += ROTATION_QUANTITY * turnoverRate_;

		//Y軸の角度が360より大きいなら0に戻す
		if (Angle > TWOPI_DEGREES) Angle = ZEROPI_DEGREES;
	}

	//当たり判定
	void OnCollision(GameObject* pTarget) override
	{
		//Playerと衝突したら
		if (pTarget->GetObjectName() == "Player")
		{
			//Playerポジションをセットする
			pTarget->SetPosition(playerPos_);

			//Playerと当たっている状態なら回転率をどんどん早める
			//もし回転率が最大まで達したら状態をMoveに設定
			(turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = Move);
		}
	}

};

