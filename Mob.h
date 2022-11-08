#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"

//■■シーンを管理するクラス
class Mob : public GameObject
{
protected:

	//モデル番号
	int hModel_;

	//ファイルネームパス
	std::string ModelNamePath_;

	//コリジョンの使用
	enum Collision
	{
		No,
		Box,
		Sphere,
	};

	//どのコリジョンを使うか
	int colliderState; 

	//当たり判定の各情報
	XMFLOAT3 pos;  //中心位置
	XMFLOAT3 size; //大きさ
	int     radius;//半径

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mob(GameObject* parent,std::string modelPath, std::string name);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//継承先ごとにUpdateでの動き方を変える
	virtual void UpdateMove() {};

	//継承先用の初期化
	virtual void ChildInitialize() {};

	//継承先用の描画
	virtual void ChildDraw() {};

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate() {};

	//継承先用のコライダー当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override { int a = 0; }

};

//コインクラス
class Coin : public Mob
{
public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}


	void ChildInitialize() override
	{
		BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1 * transform_.scale_.y, 0), XMFLOAT3(2 * transform_.scale_.x, 2 * transform_.scale_.y, 2 * transform_.scale_.z));
		AddCollider(collision);

		SetEmission();
	}

	//コインの動き方
	void UpdateMove() override
	{
		transform_.rotate_.y += 4;
	}

	//当たり判定
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			KillMe();
		}
	}
};

//ワープクラス
class Warp : public Mob
{
private:

	//定数
	const float    ROTATION_QUANTITY = 1.0f;        //回転量
	const float    ADDITION_TURNOVERRATE = 0.01f;   //回転率を加算する量
	const float    MAX_TURNOVERRATE = 10.0f;        //最大回転率
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
		,turnoverRate_(1), playerPos_(0,0,0)
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
		transform_.rotate_.y += ROTATION_QUANTITY * turnoverRate_;

		//Y軸の角度が360より大きいなら0に戻す
		if(transform_.rotate_.y > TWOPI_DEGREES) transform_.rotate_.y = ZEROPI_DEGREES;
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

