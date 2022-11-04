#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"
#include "Engine/BoxCollider.h"

//■■シーンを管理するクラス
class Mob : public GameObject
{
protected:

	//モデル番号
	int hModel_;

	//ファイルネームパス
	std::string ModelNamePath_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mob(GameObject* parent,std::string modelPath);

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

	//当たり判定
	virtual void OnCollision(GameObject* pTarget) override {};

	//継承先ごとにUpdateでの動き方を変える
	virtual void UpdateMove();

	//継承先用の初期化
	virtual void ChildInitialize();

	//継承先用の描画
	virtual void ChildDraw();

	//継承先用のスタートアップデート
	virtual void ChildStartUpdate();

};

//コインクラス
class Coin : public Mob
{
public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath) :Mob(parent, modelPath) {}

	//コインの動き方
	void UpdateMove() override;

	//継承先用のスタートアップデート
	void ChildStartUpdate() override;
};

//ワープクラス
class Warp : public Mob
{
public:

	//コンストラクタ
	Warp(GameObject* parent, std::string modelPath) :Mob(parent, modelPath)
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
			pos.y += 1;
			pTarget->SetPosition(pos);
		}
	}

};

