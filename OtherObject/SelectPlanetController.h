#pragma once
#include "UserPlanetBase.h"
#include <vector>

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{

	//星をセット
	void SetUserPlanetFirst(UserPlanetBase* pUserPlanet);
	void SetUserPlanetSecond(UserPlanetBase* pUserPlanet);
	void SetUserPlanetThird(UserPlanetBase* pUserPlanet);

	//更新処理
	void Update();
};

