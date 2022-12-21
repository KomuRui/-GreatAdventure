#pragma once
#include "UserPlanetBase.h"
#include <vector>

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//各星の情報
	std::vector<UserPlanetBase*> PlanetInfo_;

	//星をセット
	void SetUserPlanet();
};

