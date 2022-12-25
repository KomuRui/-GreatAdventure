#pragma once
#include "../Mob.h"

/// <summary>
/// �R�C���N���X
/// </summary>
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;
};
