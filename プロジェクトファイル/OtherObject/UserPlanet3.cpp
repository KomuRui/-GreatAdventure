#include "UserPlanet3.h"
#include "UserInfomation.h"

//コンストラクタ
UserPlanet3::UserPlanet3(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent, UserInfomation::GetThirdModelPath(), name)
{
}