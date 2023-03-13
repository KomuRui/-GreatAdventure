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

	/// <summary>
	/// セーブ
	/// </summary>
	/// <param name="filePath">ロードしたいファイルの名前</param>
	/// <param name="coinNum">セーブ時点でのコインの数</param>
	/// <param name="stageReleaseNum">解放ステージ数</param>
	void Save(UserInfo str, std::string filePath, int coinNum, int stageReleaseNum);

	/// <summary>
	/// セーブ関数を呼ぶ
	/// </summary>
	/// <param name="coinNum">セーブ時点でのコインの数</param>
	/// <param name="stageReleaseNum">解放ステージ数</param>
	void CallSave();

	/////各セーブ関数//////

	//コインの数と解放ステージ数を受け取る
	void FirstSave(int coinNum,int stageReleaseNum);
	void SecondSave(int coinNum, int stageReleaseNum);
	void ThirdSave(int coinNum, int stageReleaseNum);

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

