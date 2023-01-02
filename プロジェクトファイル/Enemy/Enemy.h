#pragma once
#include "../Mob.h"
#include "../Engine/Fbx.h"
#include "../State/EnemyState/EnemyState.h"

/// <summary>
/// 敵の基底クラス(ステートベースAI)
/// </summary>
class Enemy : public Mob
{
protected:

	///////////////キャラの必要な情報///////////////////

	XMVECTOR front_;        //キャラの前方向のベクトル
	XMFLOAT3 basePos_;      //探索するときのベースポジション
	bool isUseGravity_;     //重力使うかどうか
	int rotationAngle_;     //回転角度
	int rotationSign_;      //回転符号
	float dotX_;            //内積の計算した値を入れる
	float rotationTotal_;   //どのくらい回転したか

	///////////////敵の動きパターン////////////////

	EnemyState* pState_;    //状態

	int operationTime_;     //次の状態に変わるまでの時間
	int stateCount_;        //その状態になってからどのくらいの秒数たったか

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
	/// レイで当たり判定(3D用)
	/// </summary>
	/// <param name="data">当たり判定に必要なデータ</param>
	void StageRayCast(const RayCastData& data);

	/// <summary>
	/// キャラの動き(円用)
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// 探索範囲内にいるかどうか
	/// </summary>
	/// <returns>trueならいる,falseならいない</returns>
	bool IsInSearchRange();

	/// <summary>
	/// モデル番号取得
	/// </summary>
	/// <returns>モデル番号</returns>
	int GetModelNumber() { return hModel_; }

	/// <summary>
	/// 上軸の角度ゲット
	/// </summary>
	/// <returns>上軸の角度</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// 上軸の上軸の角度をセット
	/// </summary>
	/// <param name="angle">セットしたい角度</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// 次の状態に変わるまでの時間をセット
	/// </summary>
	/// <param name="time">セットしたい次の状態に変わるまでの時間</param>
	void SetOperationTime(const int& time) { operationTime_ = time; }

	/// <summary>
	/// その状態になってからどのくらいの秒数たったかをセット
	/// </summary>
	/// <param name="count">セットしたい秒数</param>
	void SetStateCount(const int& count) { stateCount_ = count; }

	/// <summary>
	/// その状態になってからどのくらいの秒数たったか
	/// </summary>
	/// <returns>その状態になってからどのくらいの秒数たったか</returns>
	int GetStateCount() { return stateCount_; }

	/// <summary>
	/// どっちに回転するか(符号)
	/// </summary>
	/// <param name="sign">セットしたい符号(1か-1)</param>
	void SetRotationSign(const int& sign) { rotationSign_ = sign; }

	/// <summary>
	/// 回転角度セット
	/// </summary>
	/// <param name="angle">セットしたい回転角度</param>
	void SetRotationAngle(const int& angle) { rotationAngle_ = angle; }

	/// <summary>
	/// どのくらい回転したかセット
	/// </summary>
	/// <param name="total">どのくらい回転したか</param>
	void SetRotationTotal(const float& total) { rotationTotal_ = total; }

	///////////////////AI用関数/////////////////////

	/// <summary>
	/// 待機
	/// </summary>
	virtual void Wait();

	/// <summary>
	/// 移動
	/// </summary>
	virtual void Move();

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

	/// <summary>
	/// 状態チェンジ
	/// </summary>
	/// <param name="state">チェンジしたい状態</param>
	void ChangeEnemyState(EnemyState* state);

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

