#pragma once
#include "../Mob/Mob.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/Model.h"

/// <summary>
/// Playerの基底クラス
/// </summary>
class PlayerBase : public Mob
{
protected:

	///////////////キャラの必要な情報///////////////////


	XMMATRIX mPreviousAngle_;          //ジャンプしているときの回転行列
	float jampRotationPreviousAngle_;  //ジャンプしているときの角度
	float acceleration_;               //重力の加速度
	float normalInterpolation_;        //法線を補間するときの補間係数
	bool  isCheckNormal_;              //法線を調べるかどうか

	/////////////////////カメラ//////////////////////

	enum Cam
	{
		LONG,          //長距離
		SHORT,         //近距離
		MAX_CAM_SIZE
	};

	XMVECTOR camVecTotal_[MAX_CAM_SIZE];//全種類のカメラの距離
	XMVECTOR camVec_;                   //Playerからカメラまでの距離
	XMMATRIX camMat_;                   //カメラの角度を変更するためのマトリクス
	XMVECTOR vCam_;                     //カメラの位置までのベクトル
									    
	int   camStatus_;                   //カメラの状態
	float camAngle_;                    //カメラの角度
	bool  isMoveCamPos_;                //カメラのポジション動くかどうか
	bool  isLockcam_;                   //カメラ固定されているのなら

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

	//描画
	void ChildDraw() override {};

	//ステージに合わせて回転
	virtual void RotationInStage() override {};

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//当たり判定
	virtual void OnCollision(GameObject* pTarget) override;

	///////////////////////////関数////////////////////////////

	/// <summary>
	/// 継承先用の更新
	/// </summary>
	virtual void ChildPlayerUpdate() {};

	/// <summary>
	/// 継承先用の初期化
	/// </summary>
	virtual void ChildPlayerInitialize() {};

	/// <summary>
	/// 継承先用のスタートアップデート
	/// </summary>
	virtual void ChildPlayerStartUpdate() {};

	/// <summary>
	/// カメラの処理
	/// </summary>
	void CameraBehavior();

	/// <summary>
	/// Playerのカメラの処理(2Dと3Dでカメラの動きが違うのでvirtualにする)
	/// </summary>
	virtual void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) {};

	/// <summary>
	/// カメラがロックされていた時のカメラの処理
	/// </summary>
	void CameraLockBehavior(XMFLOAT3 *pos, XMFLOAT3 *tar);

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	void CheckUnderNormal();

	/////////////////////セットゲット関数//////////////////////

	/// <summary>
	/// カメラの位置を動かすかセット
	/// </summary>
	void SetCamPosNotMove() { isMoveCamPos_ = false; }

	/// <summary>
	/// キャラが下の法線調べるかどうかをセット
	/// </summary>
	/// <param name="flag">調べるならtrue,調べないならfalse</param>
	void SetCheckNormal(const bool& flag) { isCheckNormal_ = flag; }

	/// <summary>
	/// カメラ動作しているかどうか
	/// </summary>
	/// <returns>動作してるならtrue,してないならfalse</returns>
	bool IsCamBehavior() { return isLockcam_; }

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
	void SetCamFlag(const bool& flag) { isLockcam_ = flag; }

	/// <summary>
	/// カメラのアングル近距離にセット
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; camVec_ = camVecTotal_[camStatus_]; CameraBehavior(); }

	/// <summary>
	/// カメラのアングル長距離にセット
	/// </summary>
	void SetCamLong() { camStatus_ = LONG;  camVec_ = camVecTotal_[camStatus_]; CameraBehavior(); }

	/// <summary>
	/// カメラまでのベクトルをセット
	/// </summary>
	void SetCamVec(const XMVECTOR& v) { vCam_ = v; }

	/// <summary>
	/// カメラが長距離かどうか
	/// </summary>
	/// <returns>trueなら長距離</returns>
	bool IsCamLong() { return (camStatus_ == LONG); }

	/// <summary>
	/// 死亡しているかどうか
	/// </summary>
	/// <returns>trueなら死亡している</returns>
	bool IsDie() { return (PlayerStateManager::playerState_ == PlayerStateManager::playerDieing_); }

	/// <summary>
	/// ジャンプしているかどうか
	/// </summary>
	/// <returns>trueならジャンプしている</returns>
	bool IsJump() { return (PlayerStateManager::playerState_ == PlayerStateManager::playerJumping_); }
};

