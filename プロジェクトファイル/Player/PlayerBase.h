#pragma once
#include "../Mob.h"
#include "../Engine/GameObject.h"

/// <summary>
/// Playerの基底クラス
/// </summary>
class PlayerBase : public Mob
{

	///////////////キャラの必要な情報///////////////////


	XMMATRIX mPreviousAngle_;          //ジャンプしているときの回転行列
	float jampRotationPreviousAngle_;  //ジャンプしているときの角度
	float acceleration_;               //重力の加速度
	bool  normalFlag_;                 //法線を調べるかどうか

	/////////////////////カメラ//////////////////////

	enum Cam
	{
		LONG,          //長距離
		SHORT,         //近距離
		MAX_CAM_SIZE
	};

	XMVECTOR camVec_[MAX_CAM_SIZE];    //Playerからカメラまでの距離  
	XMMATRIX camMat_;                  //カメラの角度を変更するためのマトリクス

	int   camStatus_;                  //カメラの状態
	float camAngle_;                   //カメラの角度
	bool  camPosFlag_;                 //カメラのポジション動くかどうか
	bool  camFlag_;                    //カメラ動作するかどうか

public:

	/// <summary>
	/// Playerの状態を表す変数
	/// </summary>
	PlayerStateManager* pState_;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	PlayerBase(GameObject* parent);


	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新の前に一回呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void Update() override;

	//継承先用の更新
	virtual void ChildPlayerUpdate() {};

	//描画
	void ChildDraw() override {};

	//ステージに合わせて回転
	void RotationInStage() override {};

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override {};

	//当たり判定
	void OnCollision(GameObject* pTarget) override {};

	///////////////////////////関数////////////////////////////

	/// <summary>
	/// カメラの処理
	/// </summary>
	void CameraBehavior() {};

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	void CheckUnderNormal() {};

	/////////////////////セットゲット関数//////////////////////

	/// <summary>
	/// カメラの位置を動かすかセット
	/// </summary>
	void SetCamPosNotMove() { camPosFlag_ = false; }

	/// <summary>
	/// キャラが下の法線調べるかどうかをセット
	/// </summary>
	/// <param name="flag">調べるならtrue,調べないならfalse</param>
	void SetCheckNormal(const bool& flag) { normalFlag_ = flag; }

	/// <summary>
	/// カメラ動作しているかどうか
	/// </summary>
	/// <returns>動作してるならtrue,してないならfalse</returns>
	bool IsCamBehavior() { return camFlag_; }

	/// <summary>
	/// Playerが回転しているかどうか
	/// </summary>
	/// <returns>回転しているならtrue,していないならfalse</returns>
	bool IsRotation() { return (PlayerStateManager::playerState_ == PlayerStateManager::playerJumpRotationning_ || PlayerStateManager::playerState_ == PlayerStateManager::playerRotationning_); }

	/// <summary>
	/// 重力をセット
	/// </summary>
	/// <param name="acceleration">セットしたい重力の値</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// ジャンプした時の軸の角度設定
	/// </summary>
	/// <param name="angle">セットしたいジャンプした時の軸の角度</param>
	void SetJampRotationPreviousAngle(const float& angle) { jampRotationPreviousAngle_ = angle; }

	/// <summary>
	/// ジャンプしてる時のPlayerの回転マトリクスゲット
	/// </summary>
	/// <returns>ジャンプしてる時のPlayerの回転マトリクス</returns>
	XMMATRIX GetmPreviousAngle() { return mPreviousAngle_; }

	/// <summary>
	/// カメラの角度ゲット
	/// </summary>
	/// <returns>カメラの角度</returns>
	float GetCamAngle() { return camAngle_; }

	/// <summary>
	/// カメラ動作するかどうかをセット
	/// </summary>
	/// <param name="flag">trueなら動作させる,falseなら動作させない</param>
	void SetCamFlag(const bool& flag) { camFlag_ = flag; }

	/// <summary>
	/// カメラのアングル近距離にセット
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; CameraBehavior(); }

	/// <summary>
	/// カメラのアングル長距離にセット
	/// </summary>
	void SetCamLong() { camStatus_ = LONG; CameraBehavior(); }
};

