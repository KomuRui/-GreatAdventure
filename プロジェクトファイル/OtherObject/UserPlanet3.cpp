#include "UserPlanet3.h"
#include "UserInfomation.h"

//�R���X�g���N�^
UserPlanet3::UserPlanet3(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent, UserInfomation::GetThirdModelPath(), name)
{
	//�V�K�쐬����Ƃ��ɌĂԊ֐���ݒ�
	ARGUMENT_INITIALIZE(this->UserCreateNewFile, UserInfomation::SetThirdNewFile);
}