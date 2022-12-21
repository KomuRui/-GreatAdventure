#pragma once
#include "../Engine/GameObject.h"

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//ユーザーの番号
	enum Number
	{
		First,
		Second,
		Third,
		MAX_NUAMBER
	};

	//初期化
	void Initialize();

	//ユーザーの情報が入っているテキストのパス
	std::string UserPathInfo[MAX_NUAMBER];
};

