#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

/// <summary>
/// ���C�����u�L����
/// </summary>
class MainMob : public Mob
{
public:

	//�R���X�g���N�^
	MainMob(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name) {}

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;
};
