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

	//first->作ったかどうか
	//second->何個作ったか
	std::pair<bool,int> create3D_;               //3Dオブジェクト
	std::pair<bool,int> createSigeboard_;        //看板
	std::pair<bool,int> createCameraTransition_; //カメラ遷移
	std::pair<bool,int> createImage_;            //画像

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