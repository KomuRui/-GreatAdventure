#pragma once
#include "Engine/GameObject.h"
#include "TutorialScene/TutorialStage.h"
#include "windowsnumerics.h"
#include "Engine/Particle.h"

using namespace Windows::Foundation::Numerics;

//■■シーンを管理するクラス
class Player : public GameObject
{

	Particle* pParticle_;

	int      hModel_;                      //モデル番号

	///////////////カメラ///////////////////

	const XMVECTOR CAM_VEC;                //Playerからカメラまでの距離  
	XMMATRIX CamMat;                       //カメラの角度を変更するためのマトリクス
	XMFLOAT3 NowCamPos;                    //カメラの前のポジションを保存しておく

	///////////////当たり判定///////////////////

	TutorialStage* pstage_;                //ステージクラスのポインタ
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

	float acceleration;             //重力の加速度
	int   rotationCount;            //回転してからどのくらいのフレームがたったか

	XMVECTOR Up;                    //キャラの上ベクトル
	XMVECTOR Down;                  //キャラの下ベクトル
	XMVECTOR vNormal;               //下の法線
	float Angle;                    //キャラの上の軸の角度
	float JampRotationPreviousAngle;//ジャンプしているときの角度
	XMMATRIX mPreviousAngle;        //ジャンプしているときのマトリクス
	XMMATRIX TotalMx;               //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMVECTOR vJamp;                 //ジャンプするときの元となる上ベクトル

	bool isJamp;                    //今ジャンプしているか
	bool isJampRotation;            //今ジャンプ回転しているか
	bool isRotation;                //今回転をしているか

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

	//ステージに合わせてPlayerを回転
	void RotationInStage();

	//ゆっくりと次の角度に向く
	void FaceOrientationSlowly(float afterRotate, bool& flag);

	//レイ(円用)
	void StageRayCast();

	//レイ(2D用)
	void StageRayCast2D();

	//プレイヤー操作(円用)
	void MovingOperation();

	//プレイヤー操作(2D用)
	void MovingOperation2D();

	//当たり判定
	void OnCollision(GameObject* pTarget) override;
};

