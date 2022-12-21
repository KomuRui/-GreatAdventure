#pragma once
#include "../../Engine/GameObject.h"

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	////定数

	const float RATATION_SPEED = 0.5f;    //回転速度
	const float BRIGHTNESS = 1.5f;		  //背景モデルの明るさ
	const XMFLOAT3 CAM_POS = { 0, 0, 5 }; //カメラの位置
	const XMFLOAT3 CAM_TAR = { 0, 0, 0 }; //カメラのターゲット

	////変数

	int hModel_; 	//モデル番号格納用

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新の前に一度だけ呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

};

