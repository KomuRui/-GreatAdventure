#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"

//■■シーンを管理するクラス
class Player : public GameObject
{
	int   hModel_;                //モデル番号
	float cameraPos_;             //カメラの角度

	const XMVECTOR CAM_VEC;       //Playerからカメラまでの距離       

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	/////////////////////関数//////////////////////

	//カメラの処理
	void CameraBehavior();

	//プレイヤー操作
	void MovingOperation();

	//ゆっくりと次の角度に向く
	void FaceOrientationSlowly(float afterRotate, bool& flag);

	//レイ
	//void MovingOperation();
};

