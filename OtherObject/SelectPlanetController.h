#pragma once
#include "UserPlanetBase.h"
#include <vector>

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{
	//�e���̏��
	std::vector<UserPlanetBase*> PlanetInfo_;

	//������
	void Initialize();

	//�����Z�b�g
	void SetUserPlanet(UserPlanetBase* pUserPlanet);

	//�X�V����
	void Update();
};

