#include "UserPlanet1.h"
#include "UserInfomation.h"

//�R���X�g���N�^
UserPlanet1::UserPlanet1(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent, UserInfomation::GetFirstModelPath() , name)
{
	//�V�K�쐬����Ƃ��ɌĂԊ֐���ݒ�
	ARGUMENT_INITIALIZE(this->UserCreateNewFile,UserInfomation::SetFirstNewFile);
}

//������
void UserPlanet1::ChildInitialize()
{
	//�Z���N�g����Ă�ɐݒ�
	ARGUMENT_INITIALIZE(isSelect_, true);
}