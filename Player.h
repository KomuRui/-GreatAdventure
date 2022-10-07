#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//■■シーンを管理するクラス
class Player : public GameObject
{
	int      hModel_;                      //モデル番号

	///////////////カメラ///////////////////

	XMFLOAT3       cameraPos_;             //カメラの角度
	const XMVECTOR CAM_VEC;                //Playerからカメラまでの距離  
	

	///////////////当たり判定///////////////////

	Stage* pstage_;                        //ステージクラスのポインタ
	int      hGroundModel_;                //ステージのモデル番号を入れる変数

	enum StageRayDecision                  //各方向への当たり判定するために列挙する
	{
		Straight = 0,                      //前
		Back,                              //後
		Left,                              //左
		Right,                             //右
		Under,                             //下
		Top,                               //上
		MAX_RAY_SIZE
	};

	XMVECTOR Up;

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
	void StageRayCast();
};

