#include "UserPlanet1.h"

//コンストラクタ
UserPlanet1::UserPlanet1(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent,modelPath,name)
{
}

//初期化
void UserPlanet1::ChildInitialize()
{
	//セレクトされてるに設定
	ARGUMENT_INITIALIZE(isSelect_, true);
}