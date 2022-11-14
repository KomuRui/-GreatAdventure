#pragma once
#include "../Mob.h"

//�R�C���N���X
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}


	void ChildStartUpdate() override
	{
		SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1 * transform_.scale_.y, 0), 1.0f * transform_.scale_.y);
		AddCollider(collision);
	}

	//�R�C���̓�����
	void UpdateMove() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			KillMe();
		}
	}
};
