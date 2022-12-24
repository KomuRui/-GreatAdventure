#pragma once
#include "../Engine/GameObject.h"

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//初期化
	void Initialize();

	//ユーザーの情報が入っているテキストのパス
	std::string firstUserPathInfo_;
	std::string secondUserPathInfo_;
	std::string thirdUserPathInfo_;
};

