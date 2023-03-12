#pragma once
#include "../Engine/GameObject/GameObject.h"

//ユーザー情報(3つのデータを持っておく)
namespace UserInfomation
{
	//ユーザー情報
	struct UserInfo
	{
		std::string modelPath; //モデルパス
		int coinNum;           //コインの数
		int stageReleaseNum;   //ステージ解放の数
	};

	//初期化
	void Initialize();

	/// <summary>
	/// ファイルロード
	/// </summary>
	/// <param name="str">ロードした結果を格納する変数のポインタ</param>
	/// <param name="filePath">ロードしたいファイルの名前</param>
	void Load(UserInfo* str,std::string filePath);

	/// <summary>
	/// 新規作成
	/// </summary>
	/// <param name="newModelPath">新しい星のモデルパス</param>
	/// <param name="filePath">ロードしたいファイルの名前</param>
	void CreateNewfile(std::string filePath, std::string newModelPath);

	/////各ゲット関数//////

	//各星のモデルパス取得
	std::string GetFirstModelPath();
	std::string GetSecondModelPath();
	std::string GetThirdModelPath();

	//各星のユーザー情報が入っているテキストのパス取得
	std::string GetFirstInfoPath();
	std::string GetSecondInfoPath();
	std::string GetThirdInfoPath();

	///////各セット関数///////

	/// <summary>
	/// 各星を新規作成するときに呼ぶ関数
	/// </summary>
	/// <param name="newModelPath">新しい星のモデルパス</param>
	void SetFirstNewFile(std::string newModelPath);
	void SetSecondNewFile(std::string newModelPath);
	void SetThirdNewFile(std::string newModelPath);
};

