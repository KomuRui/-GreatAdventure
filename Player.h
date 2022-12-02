#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "windowsnumerics.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"

using namespace Windows::Foundation::Numerics;

class Player : public GameObject
{

	///////////////キャラの必要な情報///////////////////

	//定数

	const float ANIM_SPEED = 1.0f;         //アニメーションの再生速度
	const int ANIM_START_FRAME = 1;        //アニメーションの開始フレーム
	const int ANIM_END_FRAME = 60;		   //アニメーションの終了フレーム

	//変数

	Particle* pParticle_;                  //エフェクト表示するのに必要な変数

	XMMATRIX mPreviousAngle_;              //ジャンプしているときのマトリクス
	XMMATRIX totalMx_;					   //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMVECTOR front_;                       //キャラの前方向のベクトル
	XMVECTOR up_;                          //キャラの上ベクトル
	XMVECTOR down_;					       //キャラの下ベクトル
	XMVECTOR vNormal_;                     //キャラの下のステージの法線
	XMVECTOR vJamp_;                       //ジャンプするときの元となる上ベクトル
	XMVECTOR keepJamp_;                    //もととなるジャンプベクトルを保存しておく

	float angle_;                          //キャラの上の軸の角度
	float jampRotationPreviousAngle_;      //ジャンプしているときの角度
	float acceleration_;                   //重力の加速度

    int   hModel_;                         //モデル番号
	int   rotationCount_;                  //回転してからどのくらいのフレームがたったか

	bool  isJamp_;                         //今ジャンプしているか
	bool  isJampRotation_;                 //今ジャンプ回転しているか
	bool  isRotation_;                     //今回転をしているか
	bool  isFly_;                          //今浮いているかどうか
	bool  normalFlag_;                     //法線を調べるかどうか

	///////////////カメラ///////////////////

	enum Cam
	{
		LONG,                              //長距離
		SHORT,                             //近距離
		MAX_CAM_SIZE
	};

	XMVECTOR camVec_[MAX_CAM_SIZE];        //Playerからカメラまでの距離  
	XMMATRIX camMat_;                      //カメラの角度を変更するためのマトリクス
	
    int   camStatus_;                      //カメラの状態
	float camAngle_;                       //カメラの角度
	bool  camPosFlag_;                     //カメラのポジション動くかどうか

	///////////////当たり判定///////////////////

	//定数

	const XMFLOAT3 COLLIDER_POS  = { 0,0,0 }; //コライダーの位置
	const float    COLLIDER_SIZE = 1.0f;      //コライダーのサイズ

	//変数

	Stage* pstage_;                           //ステージクラスのポインタ
	int      hGroundModel_;                   //ステージのモデル番号を入れる変数

	enum StageRayDecision                     //各方向への当たり判定するために列挙する
	{
		Straight = 0,                         //前
		Back,                                 //後
		Left,                                 //左
		Right,                                //右
		Under,                                //下
		Top,                                  //上
		MAX_RAY_SIZE
	};
	

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

	//落下エフェクト
	void FallEffect();

	//継承先用の指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	/////////////////////セットゲット関数//////////////////////

	//Playerを真逆の状態に設定(まったく反対に設定すると外積が０になってしまうので少しずらす)
	void SetInverseNormalAndDown() { vNormal_ = -vNormal_; vNormal_ += {0, 0.1, 0, 0}; down_ = -vNormal_; }

	//カメラを動かさないセット
	void SetCamPosFlag() { camPosFlag_ = false; }

	//法線調べるかどうかセット
	void SetNormalFlag(const bool& flag) { normalFlag_ = flag; }

	//Playerが回転をしているか
	bool GetRotationFlag() { return (isRotation_ || isJampRotation_); }

	//法線ゲット
	XMVECTOR GetNormal() { return vNormal_; }
};

