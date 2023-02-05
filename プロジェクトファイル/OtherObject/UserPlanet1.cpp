#include "UserPlanet1.h"
#include "UserInfomation.h"

//コンストラクタ
UserPlanet1::UserPlanet1(GameObject* parent, std::string modelPath, std::string name)
	:UserPlanetBase(parent, UserInfomation::GetFirstModelPath() , name)
{
	//新規作成するときに呼ぶ関数を設定
	ARGUMENT_INITIALIZE(this->UserCreateNewFile,UserInfomation::SetFirstNewFile);
}

//初期化
void UserPlanet1::ChildInitialize()
{
	//セレクトされてるに設定
	ARGUMENT_INITIALIZE(isSelect_, true);
}