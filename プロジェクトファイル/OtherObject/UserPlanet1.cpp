#include "UserPlanet1.h"

//�R���X�g���N�^
UserPlanet1::UserPlanet1(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent,modelPath,name)
{
}

//������
void UserPlanet1::ChildInitialize()
{
	//�Z���N�g����Ă�ɐݒ�
	ARGUMENT_INITIALIZE(isSelect_, true);
}