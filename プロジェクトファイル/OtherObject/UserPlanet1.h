#pragma once
#include "UserPlanetBase.h"

//���[�U�[�̐�
class UserPlanet1 : public UserPlanetBase
{

public:

	//�R���X�g���N�^
	UserPlanet1(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;
};

