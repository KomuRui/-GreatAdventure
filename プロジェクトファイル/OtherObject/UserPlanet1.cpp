#include "UserPlanet1.h"

//コンストラクタ
UserPlanet1::UserPlanet1(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent,modelPath,name)
{
}

//更新の前に一度だけ呼ばれる関数
void UserPlanet1::ChildStartUpdate()
{

}