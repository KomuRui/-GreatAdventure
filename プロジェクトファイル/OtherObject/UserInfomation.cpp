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

	//各星の情報
	UserInfo first_;
	UserInfo second_;
	UserInfo third_;

	//初期化
	void Initialize()
	{
		//各ファイルロード
		Load(&first_, FIRST_USER_INFO_PATH);
		Load(&first_,SECOND_USER_INFO_PATH);
		Load(&first_, THIRD_USER_INFO_PATH);
	};

	//ファイルロード
	void Load(UserInfo* str, std::string filePath)
	{
		//ファイルオープン
		std::ifstream ifs(filePath);

		//データを1列入れる変数
		std::string buf;

		//必要な各パラメータを保存する用の文字列配列
		std::string data[3] = { "" };

		//,の数
		int sum = ZERO;

		//1列bufに格納
		std::getline(ifs, buf);

		//bufのサイズ分ループ
		for (int i = ZERO; i < buf.size(); i++)
		{
			//各パラメータを一つずつdataに格納していく
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//各情報格納
		str->modelPath = data[0];
		str->coinNum = std::stoi(data[1]);
		str->stageReleaseNum = std::stoi(data[2]);
	}

	//新規作成
	void CreateNewfile(std::string filePath, std::string newModelPath)
	{
		//ファイルオープン
		std::ofstream ofs(filePath, std::ios::out);
		ofs << newModelPath + ",0,1";
	}

	///////各ゲット関数///////

	//各星のモデルパス取得
	std::string GetFirstModelPath()  { return first_.modelPath; }
	std::string GetSecondModelPath() { return second_.modelPath;}
	std::string GetThirdModelPath()  { return third_.modelPath; }

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