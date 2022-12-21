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

	//各ステージのブロックのトランスフォームを保存
	std::vector<Block*> tBlock_;

public:

	//コンストラクタ
	CreateStage();

	//オブジェクト作成
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	//各ステージのファイルロードしステージを作成してくれる
	void LoadFileCreateStage(GameObject* parent, std::string filename);

	//各ステージのファイルロードだけしてくれる
	void LoadFile(GameObject* parent, std::string filename);

	//LoadFileを使ってロードしたファイルを元にステージを作成
	void LoadFileBasedCreateStage();

	//各ブロックのポインタゲット
	std::vector<Block*> GetTransformBlock() { return tBlock_; }
};
