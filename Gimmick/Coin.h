#pragma once
#include "../Mob.h"

//コインクラス
class Coin : public Mob
{
public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}


	void ChildStartUpdate() override
	{
		SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1 * transform_.scale_.y, 0), 1.0f * transform_.scale_.y);
		AddCollider(collision);
	}

	//コインの動き方
	void UpdateMove() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			KillMe();
		}
	}
};
