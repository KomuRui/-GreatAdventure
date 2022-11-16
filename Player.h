#pragma once
#include "Engine/GameObject.h"
#include "TutorialScene/TutorialStage.h"
#include "windowsnumerics.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"

using namespace Windows::Foundation::Numerics;

//■■シーンを管理するクラス
class Player : public GameObject
{
	///////////////キャラの必要な情報///////////////////
	Particle* pParticle_;

	XMMATRIX mPreviousAngle;               //ジャンプしているときのマトリクス
	XMMATRIX TotalMx;					   //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMVECTOR front;                        //キャラの前方向のベクトル
	XMVECTOR Up;                           //キャラの上ベクトル
	XMVECTOR Down;					       //キャラの下ベクトル
	XMVECTOR vNormal;                      //キャラの下のステージの法線
	XMVECTOR vJamp;                        //ジャンプするときの元となる上ベクトル
	XMVECTOR KeepJamp;                     //もととなるジャンプベクトルを保存しておく

	float Angle;                           //キャラの上の軸の角度
	float JampRotationPreviousAngle;       //ジャンプしているときの角度

    int   hModel_;                         //モデル番号
	int   rotationCount;                   //回転してからどのくらいのフレームがたったか

	bool  isJamp;                          //今ジャンプしているか
	bool  isJampRotation;                  //今ジャンプ回転しているか
	bool  isRotation;                      //今回転をしているか


	///////////////カメラ///////////////////

	enum Cam
	{
		LONG,                              //長距離
		SHORT,                             //近距離
		MAX_CAM_SIZE
	};

	XMVECTOR CAM_VEC[MAX_CAM_SIZE];        //Playerからカメラまでの距離  
	XMMATRIX CamMat;                       //カメラの角度を変更するためのマトリクス
	
    int   camStatus_;                      //カメラの状態
	float camAngle_;                       //カメラの角度

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
	void StageRayCast(RayCastData* data);

	//レイ(2D用)
	void StageRayCast2D();

	//プレイヤー操作(円用)
	void MovingOperation(RayCastData* data);

	//プレイヤー操作(2D用)
	void MovingOperation2D();

	//回転エフェクト
	void RotationEffect();

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	/////////////////////セットゲット関数//////////////////////

	//Playerを真逆の状態に設定(まったく反対に設定すると外積が０になってしまうので少しずらす)
	void SetInverseNormalAndDown() { vNormal = -vNormal; vNormal += {0, 0.1, 0, 0}; Down = -vNormal; }

	//Playerが回転をしているか
	bool GetRotationFlag() { return (isRotation || isJampRotation); }
};

