#include "UserInfomation.h"
#include <fstream>

//定数
namespace
{
	//プレイヤーの総人数
	static const int TOTAL_PLAYER = 3;
}

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//ユーザーの情報が入っているテキストのパス
	std::string firstUserModelPath_;
	std::string secondUserModelPath_;
	std::string thirdUserModelPath_;

	//初期化
	void Initialize()
	{
		//各ファイルロード
		Load(&firstUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo1.txt");
		Load(&secondUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo2.txt");
		Load(&thirdUserModelPath_, "Stage/UserSelect/UserInformation/UserInfo3.txt");
	};

	//ファイルロード
	void Load(std::string* str, std::string filePath)
	{
		//ファイルオープン
		std::ifstream ifs(filePath);

		//末尾まで読む
		while (!ifs.eof())
		{
			//1列bufに格納
			std::getline(ifs, *str);
		}
	}

	//各ゲット関数
	std::string GetFirstModelPath() { return firstUserModelPath_; }
	std::string GetSecondModelPath() { return secondUserModelPath_; }
	std::string GetThirdModelPath() { return thirdUserModelPath_; }
}