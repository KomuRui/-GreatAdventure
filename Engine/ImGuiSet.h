#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"
#include "../Block/Block.h"

//最大のImguiで出せるオブジェクトサイズ
const int MAX_OBJECT_SIZE = 50;


//■■シーンを管理するクラス
class ImGuiSet : public GameObject
{
	//表示させたオブジェクトを格納する場所
	//first->モデル番号
	//second->モデル番号ごとのトランスフォーム
	std::vector<std::pair<int,Transform>>obj_;

	std::pair<bool,int> create3D_;
	std::pair<bool,int> createSigeboard_;
	std::pair<bool,int> createCameraTransition_;
	std::pair<bool,int> createImage_;

	//3Dを作るボタンを押したかどうか
	//bool create3Dflag_;

	//看板を作るボタンを押したかどうか
	//bool createSigeboardflag_;

	//カメラ遷移を作るボタンを押したかどうか
	//bool createCameraTransitionflag_;

	//画像を作るボタンを押したかどうか
	//bool createImage_;

	//3Dを何個作ったか
	//int objectCount_;

	//看板何個作ったか
	//int sigeboardCount_;

	//カメラ遷移を何個作ったか
	//int cameraTransitionCount_;


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
	
	//画像作成
	void CreateImage();

	//開放
	void Release() override;

	//更新の前に一度だけ呼ばれる関数
	void StartUpdate() override;

};