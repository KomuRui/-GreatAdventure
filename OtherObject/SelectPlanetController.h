#pragma once
#include "UserPlanetBase.h"
#include <vector>

//���[�U�[����I������Ƃ��ɊǗ�
namespace SelectPlanetController
{

	//�����Z�b�g
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet);
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet);
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet);

	//�X�V����
	void Update();
};

