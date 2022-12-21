#pragma once
#include "UserPlanetBase.h"
#include <vector>

//ユーザー情報を選択するときに管理
namespace SelectPlanetController
{
	//各星の情報
	std::vector<UserPlanetBase*> PlanetInfo_;

	//初期化
	void Initialize();

	//星をセット
	void SetUserPlanet(UserPlanetBase* pUserPlanet);

	//更新処理
	void Update();
};

