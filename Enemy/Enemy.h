#pragma once
#include "../Mob.h"
#include "../TutorialScene/TutorialStage.h"

class Enemy : public Mob
{
protected:

	///////////////敵の動きパターン////////////////

	int aiState_;         //現在の動きの状態
	int operationTime_;   //次の状態に変わるまでの時間

	XMVECTOR moveDir_;    //キャラが動く方向

	//AIの行う行動の順番
	enum EnemyAiState
	{
		MOVE,             //移動
		WAIT,             //待機
		ROTATION,         //回転
		MAX_AI_STATE
	};

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

	XMVECTOR Up;                    //キャラの上ベクトル
	XMVECTOR Down;                  //キャラの下ベクトル
	XMVECTOR vNormal;               //下の法線
	float Angle;                    //キャラの上の軸の角度

	XMMATRIX TotalMx;               //キャラの横軸のいままでのマトリクスの総括マトリクス

public:
	//コンストラクタ
	Enemy(GameObject* parent, std::string modelPath);

	//初期化
	void ChildInitialize() override;

	//更新
	void UpdateMove() override;

	//描画
	void ChildDraw() override;

	//更新の前に一回呼ばれる関数
	void ChildStartUpdate();

	//ステージに合わせてキャラを回転
	void RotationInStage();

	//レイ(円用)
	void StageRayCast();

	//キャラの動き(円用)
	void MovingOperation();

	///////////////////AI行動関数/////////////////////

	//待機
	void Wait();

	//移動
	void Move();

	//回転
    void Rotation();
};

