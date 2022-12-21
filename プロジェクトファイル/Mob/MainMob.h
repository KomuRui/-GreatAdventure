#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

//���C�����u�N���X
class MainMob : public Mob
{
public:

	//�R���X�g���N�^
	MainMob(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name) {}

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override
	{
		//�A�j���[�V����
		Model::SetAnimFrame(hModel_, 0, 120, 1);
		Model::SetAnimFlag(hModel_,true);
	}
};
