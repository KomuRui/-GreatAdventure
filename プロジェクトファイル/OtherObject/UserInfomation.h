#pragma once
#include "../Engine/GameObject.h"

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//初期化
	void Initialize();

	/// <summary>
	/// ファイルロード
	/// </summary>
	/// <param name="str">ロードした結果を格納する変数のポインタ</param>
	/// <param name="filePath">ロードしたいファイルの名前</param>
	void Load(std::string* str,std::string filePath);

	//各ゲット関数
	std::string GetFirstModelPath();
	std::string GetSecondModelPath();
	std::string GetThirdModelPath();
};

