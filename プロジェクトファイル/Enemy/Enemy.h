#pragma once
#include "../Mob.h"
#include "../Engine/Fbx.h"
#include "../State/EnemyState/EnemyStateManager.h"

/// <summary>
/// 敵の基底クラス(ステートベースAI)
/// </summary>
class Enemy : public Mob
{
protected:

	///////////////キャラの必要な情報///////////////////

	XMVECTOR front_;        //キャラの前方向のベクトル

	///////////////敵の動きパターン////////////////

	//状態
	EnemyStateManager* pState_;

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

	///////////////その他///////////////////

	int    hGroundModel_;   //ステージのモデル番号を入れる変数
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

	///////////////////関数/////////////////////

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// ステージに合わせてキャラを回転
	/// </summary>
	void RotationInStage();
	
	/// <summary>
	/// レイで当たり判定(3D用)
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void StageRayCast(const RayCastData& data);

	/// <summary>
	/// キャラの動き(円用)
	/// </summary>
	/// <param name="data"></param>
	void MovingOperation(const RayCastData& data);

	///////////////////AI用関数/////////////////////

	/// <summary>
	/// 待機
	/// </summary>
	virtual void Wait();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="data">レイキャストのデータ</param>
	virtual void Move(const RayCastData& data);

    /// <summary>
    /// 回転
    /// </summary>
	virtual void Rotation();

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
	virtual void PlayerNearWithIsCheck();

	/// <summary>
	/// 状態をゲット
	/// </summary>
	/// <returns>現在の状態</returns>
	EnemyState* GetEnemyState() { return pState_; }

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

