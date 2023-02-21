#pragma once
#include "Transform.h"
#include "GameObject.h"
#include "../Block/Block.h"

//各ステージでカメラ遷移するときの必要な情報
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //カメラのポジション
	XMFLOAT3 CameraTarget;    //カメラのターゲット
	XMFLOAT3 CollisionSize;   //コライダーのサイズ
};

//各シーンのステージ作ってくれる
class CreateStage
{
	//ステージ作成に必要な情報
	struct CreateStageInfo
	{
		GameObject* parent;         //親オブジェクト
		std::string ModelPathName;  //モデルパスネーム
		std::string inName;         //オブジェクトの名前
		Transform   t;              //トランスフォーム
		XMFLOAT3    camPos;         //カメラのポジション(必要なオブジェクトと必要じゃないオブジェクトがある)
	};

	//光るライトのコントローラーを一度しか作らないのでflagで作ったかどうか確認する
	bool createShineController_;

	//ファイルロードして得た情報を保存しておく(LoadFileという関数で使う)
	//好きなタイミングでステージ制作できるように
	std::vector<CreateStageInfo> info_;

	//作成したステージのオブジェクト全て保存しておく
	std::vector<GameObject*> createStageAllObject_;

	//各ステージのブロックのトランスフォームを保存
	std::vector<Block*> tBlock_;

public:

	//コンストラクタ
	CreateStage();

	//オブジェクト作成
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	/// <summary>
	/// 各ステージのファイルロードしステージを作成してくれる
	/// </summary>
	/// <param name="parent">作成するステージの親オブジェクト</param>
	/// <param name="filename">ロードしたいファイル</param>
	void LoadFileCreateStage(GameObject* parent, std::string filename);

	/// <summary>
	/// 各ステージのファイルロードだけしてくれる 
	/// </summary>
	/// <param name="parent">作成するステージの親オブジェクト</param>
	/// <param name="filename">ロードしたいファイル</param>
	void LoadFile(GameObject* parent, std::string filename);

	/// <summary>
	/// LoadFileを使ってロードしたファイルを元にステージを作成
	/// </summary>
	void LoadFileBasedCreateStage();

	/// <summary>
	/// 作成したステージをすべて削除
	/// </summary>
	void AllCreateStageDelete();

	/// <summary>
	/// 作成したステージすべて描画と更新しないように
	/// </summary>
	void AllCreateStageInvisibleAndLeave();

	/// <summary>
	/// 作成したステージすべて描画と更新するように
	/// </summary>
	void AllCreateStageVisibleAndEnter();

	/// <summary>
	/// 各ブロックのポインタゲット
	/// </summary>
	/// <returns>各ブロックのポインタ保管しているvector</returns>
	std::vector<Block*> GetTransformBlock() { return tBlock_; }

	/// <summary>
	/// 普通型の生成(画像やMobを継承していないゲームオブジェクト)
	/// </summary>
	/// <typeparam name="T">生成したいクラスの名前</typeparam>
	/// <param name="pParent">親</param>
	template <class T>
	T* InstantiateNormal(GameObject* pParent,std::string modelPath,std::string name, Transform t);

	//普通型の生成(名前とモデルパス指定しない)
	template <class T>
	T* InstantiateNormal(GameObject* pParent,Transform t);

	//Mobを継承した3Dオブジェ生成
	template <class T>
	T* InstantiateMob3D(GameObject* pParent, std::string modelPath, std::string name, Transform t);

	//ボタンの生成
	template <class T>
	T* InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform t);

	//ブロックの生成
	template <class T>
	T* InstantiateBlock(GameObject* pParent, std::string modelPath, std::string name, Transform t);

	//星の生成
	template <class T>
	T* InstantiatePlanet(GameObject* pParent, std::string modelPath, std::string name, Transform t);
};
