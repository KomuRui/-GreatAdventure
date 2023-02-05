#include "UserInfomation.h"
#include <fstream>

//定数
namespace
{
	//プレイヤーの総人数
	static const int TOTAL_PLAYER = 3;

	//各ユーザー情報が入っているテキストのパス
	static const std::string FIRST_USER_INFO_PATH =  "Stage/UserSelect/UserInformation/UserInfo1.txt";
	static const std::string SECOND_USER_INFO_PATH = "Stage/UserSelect/UserInformation/UserInfo2.txt";
	static const std::string THIRD_USER_INFO_PATH =  "Stage/UserSelect/UserInformation/UserInfo3.txt";
}

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//各星のモデルのパス
	std::string firstModelPath_;
	std::string secondModelPath_;
	std::string thirdModelPath_;

	//初期化
	void Initialize()
	{
		//各ファイルロード
		Load(&firstModelPath_, FIRST_USER_INFO_PATH);
		Load(&secondModelPath_,SECOND_USER_INFO_PATH);
		Load(&thirdModelPath_, THIRD_USER_INFO_PATH);
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

	//新規作成
	void CreateNewfile(std::string filePath, std::string newModelPath)
	{
		//ファイルオープン
		std::ofstream ofs(filePath, std::ios::out);
		ofs << newModelPath;
	}

	///////各ゲット関数///////

	//各星のモデルパス取得
	std::string GetFirstModelPath()  { return firstModelPath_; }
	std::string GetSecondModelPath() { return secondModelPath_; }
	std::string GetThirdModelPath()  { return thirdModelPath_; }

	//各星のユーザー情報が入っているテキストのパス取得
	std::string GetFirstInfoPath()  { return FIRST_USER_INFO_PATH; }
	std::string GetSecondInfoPath() { return SECOND_USER_INFO_PATH; }
	std::string GetThirdInfoPath()  { return THIRD_USER_INFO_PATH; }


	///////各セット関数///////

	//各星を新規作成するときに呼ぶ関数
	void SetFirstNewFile(std::string newModelPath) { CreateNewfile(FIRST_USER_INFO_PATH, newModelPath); }
	void SetSecondNewFile(std::string newModelPath) { CreateNewfile(SECOND_USER_INFO_PATH, newModelPath); }
	void SetThirdNewFile(std::string newModelPath) { CreateNewfile(THIRD_USER_INFO_PATH, newModelPath); }
}