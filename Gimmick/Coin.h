#pragma once
#include "../Mob.h"

//�R�C���N���X
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}


	void ChildInitialize() override
	{
		BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1 * transform_.scale_.y, 0), XMFLOAT3(2 * transform_.scale_.x, 2 * transform_.scale_.y, 2 * transform_.scale_.z));
		AddCollider(collision);

		SetEmission();
	}

	//�R�C���̓�����
	void UpdateMove() override
	{
		transform_.rotate_.y += 4;
	}

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			KillMe();
		}
	}
};
