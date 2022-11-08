#pragma once
#include "../Mob.h"

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
