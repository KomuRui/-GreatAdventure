#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Player.h"

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
public:

	//コンストラクタ
	Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath,name){}


	void ChildInitialize() override
	{
		BoxCollider* collision = new BoxCollider(XMFLOAT3(0, -2, 0), XMFLOAT3(5.5, 4, 5.5));
		AddCollider(collision);
	}

	//ワープの動き方
	void UpdateMove() override 
	{ 
		transform_.rotate_.y += 2;

		if (transform_.rotate_.y > 360)
			transform_.rotate_.y = 0;
	}

	//当たり判定
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			XMFLOAT3 pos = transform_.position_;
			pos.y -= 0.5;
			pTarget->SetPosition(pos);

			transform_.rotate_.y = 0;

		}
	}

};

