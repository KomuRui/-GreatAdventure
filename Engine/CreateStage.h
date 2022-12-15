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

	//光るライトのコントローラーを一度しか作らないのでflagで作ったかどうか確認する
	bool CreateShineController;

	//各ステージのブロックのトランスフォームを保存
	std::vector<Block*> tBlock;

public:

	//コンストラクタ
	CreateStage();

	//オブジェクト作成
	void CreateObject(GameObject* parent,std::string ModelPathName, std::string inName, Transform t, XMFLOAT3 camPos);

	//各ステージのファイルロード
	void LoadFile(std::string filename);

	//各ブロックのポインタゲット
	std::vector<Block*> GetTransformBlock() { return tBlock; }
};
