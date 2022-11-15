#pragma once
#include "../Mob.h"
#include "../Player.h"

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
	int      number_;        //ワープの番号
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
		, turnoverRate_(1), playerPos_(0, 0, 0), number_(0)
	{}

	//スタートアップデート
	void ChildStartUpdate() override
	{
		//自身に当たり判定を追加
		BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
		AddCollider(collision);

		//ワープにPlayerを乗せるときのPlayerのポジションを設定
		XMStoreFloat3(&playerPos_,XMVector3Normalize(-vNormal));

		playerPos_ = Transform::Float3Add(transform_.position_, playerPos_);
	}

	//ワープの動き方
	void ChildUpdate() override
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

			//number_が1の状態なら
			if (number_ == 1)
			{
				Player *pPlayer_ = (Player*)FindObject("Player");
				pPlayer_->SetInverseNormalAndDown();
				number_ = 0;
			}

			//Playerと当たっている状態なら回転率をどんどん早める
			//もし回転率が最大まで達したら状態をMoveに設定
			(turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = Move);
		}
	}

	//ワープの番号セット
	void SetNumber(int num) { number_ = num; }
};

