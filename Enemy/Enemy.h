#pragma once
#include "../Mob.h"
#include "../TutorialScene/TutorialStage.h"
#include "../Engine/Fbx.h"
#include "../Player.h"

class Enemy : public Mob
{
protected:

	///////////////キャラの必要な情報///////////////////

	XMVECTOR front_;        //キャラの前方向のベクトル

	///////////////敵の動きパターン////////////////

	int aiState_;           //現在の動きの状態
	int operationTime_;     //次の状態に変わるまでの時間
	int stateCount_;        //その状態になってからどのくらいの秒数たったか
	int rotationAngle_;     //回転角度
	int rotationSign_;      //回転符号
	float dotX_;            //内積の計算した値を入れる
	float rotationTotal_;   //どのくらい回転したか
	Player* pPlayer_;       //プレイヤーの情報

	//AIの行う行動の順番
	enum EnemyAiState
	{
		MOVE,               //移動
		WAIT,               //待機
		ROTATION,           //回転
		KNOCKBACK_DIE,      //ノックバック死亡
		DIE,                //普通の死亡
		MAX_AI_STATE
	};

	///////////////当たり判定///////////////////

	int    hGroundModel_;   //ステージのモデル番号を入れる変数

	enum StageRayDecision   //各方向への当たり判定するために列挙する
	{
		Straight = 0,       //前
		Back,               //後
		Left,               //左
		Right,              //右
		Under,              //下
		Top,                //上
		MAX_RAY_SIZE
	};

	float acceleration;     //重力の加速度


public:
	//コンストラクタ
	Enemy(GameObject* parent, std::string modelPath, std::string name);

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	//更新の前に一回呼ばれる関数
	void ChildStartUpdate() override;

	//ステージに合わせてキャラを回転
	void RotationInStage();

	//レイ(円用)
	void StageRayCast(RayCastData* data);

	//キャラの動き(円用)
	void MovingOperation(RayCastData* data);

	///////////////////AI用関数/////////////////////

	//待機
	void Wait();

	//移動
	void Move(RayCastData* data);

	//回転
    void Rotation();

	//ノックバックして死亡
	virtual void KnockBackDie() {};

	//死亡
	virtual void Die() {};

	//Playerが視角内,指定距離内にいるかどうか調べる
	void PlayerNearWithIsCheck();

	//Playerの方向へ移動
	void MovingLookPlayer();

	///////////////////継承先用関数/////////////////////

	//継承先ごとにUpdateでの動き方を変える
	virtual void EnemyChildUpdate() {};

	//継承先用の初期化
	virtual void EnemyChildInitialize() {};

	//継承先用の描画
	virtual void EnemyChildDraw() {};

	//継承先用のスタートアップデート
	virtual void EnemyChildStartUpdate() {};

	//Playerが視角内、指定距離内にいた時の処理(継承用)
	virtual void PlayerWithIf() {};

	//Playerが視角内、指定距離内にいない時の処理(継承用)
	virtual void NotPlayerWithIf() {};
	 
	//継承先用のコライダー当たった時に呼ばれる関数
	virtual void OnCollision(GameObject* pTarget) override {};

	//継承先用の指定した時間で呼ばれるメソッド
	virtual void TimeMethod() override {};
};

