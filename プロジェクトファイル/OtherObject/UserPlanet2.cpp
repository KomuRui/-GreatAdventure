#include "UserPlanet2.h"
#include "UserInfomation.h"

//�R���X�g���N�^
UserPlanet2::UserPlanet2(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent, UserInfomation::GetSecondModelPath(), name)
{
}