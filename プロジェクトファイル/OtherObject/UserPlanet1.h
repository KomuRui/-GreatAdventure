#pragma once
#include "UserPlanetBase.h"

//ユーザーの星
class UserPlanet1 : public UserPlanetBase
{

public:

	//コンストラクタ
	UserPlanet1(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる関数
	void ChildStartUpdate() override;
};

