#pragma once
#include "../Mob.h"
#include "../Engine/Fbx.h"

/// <summary>
/// 敵の基底クラス(ステートベースAI)
/// </summary>
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

	//AIの行う行動
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

	/// <summary>
	/// 待機
	/// </summary>
	void Wait();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="data">レイキャストのデータ</param>
	void Move(RayCastData* data);

    /// <summary>
    /// 回転
    /// </summary>
    void Rotation();

	/// <summary>
	/// ノックバックして死亡
	/// </summary>
	virtual void KnockBackDie() {};

	/// <summary>
	/// 死亡
	/// </summary>
	virtual void Die() {};

	/// <summary>
	/// Playerが視角内,指定距離内にいるかどうか調べる
	/// </summary>
	void PlayerNearWithIsCheck();

	/// <summary>
	/// Playerの方向へ移動
	/// </summary>
	void MovingLookPlayer();

	///////////////////継承先用関数/////////////////////

	/// <summary>
	/// 継承先ごとにUpdateでの動き方を変える
	/// </summary>
	virtual void EnemyChildUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void EnemyChildInitialize() {};

	/// <summary>
	/// 継承先用の描画
	/// </summary>
	virtual void EnemyChildDraw() {};

	/// <summary>
	/// 継承先用のスタートアップデート
	/// </summary>
	virtual void EnemyChildStartUpdate() {};

	/// <summary>
	/// Playerが視角内、指定距離内にいた時の処理(継承用)
	/// </summary>
	virtual void PlayerWithIf() {};

	/// <summary>
	/// Playerが視角内、指定距離内にいない時の処理(継承用)
	/// </summary>
	virtual void NotPlayerWithIf() {};

	/// <summary>
	/// 継承先用のコライダー当たった時に呼ばれる関数
	/// </summary>
	/// <param name="pTarget">当たったオブジェクトのポインタ</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// 継承先用の指定した時間で呼ばれるメソッド
	/// </summary>
	virtual void TimeMethod() override {};
};

