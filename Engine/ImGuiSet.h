#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

//最大のImguiで出せるオブジェクトサイズ
const int MAX_OBJECT_SIZE = 50;

//各ステージでカメラ遷移するときの必要な情報
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //カメラのポジション
	XMFLOAT3 CameraTarget;    //カメラのターゲット
	XMFLOAT3 CollisionSize;   //コライダーのサイズ
};

//■■シーンを管理するクラス
class ImGuiSet : public GameObject
{
	//表示させたオブジェクトを格納する場所
	//first->モデル番号
	//second->モデル番号ごとのトランスフォーム
	std::vector<std::pair<int,Transform>>obj;

	//3Dを作るボタンを押していたらtrue
	bool Create3Dflag;

	//看板を作るボタンを押したら
	bool CreateSigeboardflag;

	//カメラ遷移を作るボタンを押したら
	bool CreateCameraTransitionflag;

	//光るライトのコントローラーを一度しか作らないのでflagで作ったかどうか確認する
	bool CreateShineController;

	//3Dを何個作ったか
	int ObjectCount;

	//看板何個作ったか
	int SigeboardCount;

	//カメラ遷移を何個作ったか
	int CameraTransitionCount;

	//トランスフォーム保存するために持っておく
	Player* pPlayer_;

	//各ステージのブロックのトランスフォームを保存
	std::vector<Block*> tBlock;

	//各ステージのカメラ遷移するときの各情報を保存
	std::vector<StageCameraTransition> CameraTransition;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ImGuiSet(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//3Dオブジェクト作成
	void Create3D();

	//看板作成
	void CreateSigeboard();

	//カメラの遷移作成(コライダーに当たったらカメラのポジション変える機能)
	void CreateCameraTransition();

	//開放
	void Release() override;

	void StartUpdate() override;

	void CreateStage(std::string filename);

	void InstantiateString(std::string ModelPathName, std::string inName, Transform t,XMFLOAT3 camPos);

	std::vector<Block*> GetTransformBlock() { return tBlock; }
};