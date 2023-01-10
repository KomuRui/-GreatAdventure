#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"
#include "State/PlayerState/PlayerStateManager.h"
#include "Engine/Model.h"


/// <summary>
/// Playerの基本クラス
/// </summary>
class Player : public GameObject
{

	///////////////キャラの必要な情報///////////////////

	////変数

	Particle* pParticle_;                   //エフェクト表示するのに必要な変数
	 
	XMMATRIX mPreviousAngle_;               //ジャンプしているときのマトリクス
	XMMATRIX totalMx_;					    //キャラの横軸のいままでのマトリクスの総括マトリクス

	XMFLOAT3 beforePos_;                    //移動する前のポジション
	XMVECTOR front_;                        //キャラの前方向のベクトル
	XMVECTOR up_;                           //キャラの上ベクトル
	XMVECTOR down_;					        //キャラの下ベクトル
	XMVECTOR vNormal_;                      //キャラの下のステージの法線
	XMVECTOR vJamp_;                        //ジャンプするときの元となる上ベクトル
	XMVECTOR keepJamp_;                     //もととなるジャンプベクトルを保存しておく

	float angle_;                           //キャラの上の軸の角度
	float jampRotationPreviousAngle_;       //ジャンプしているときの角度
	float acceleration_;                    //重力の加速度

    int   hModel_;                          //モデル番号
	int   rotationCount_;                   //回転してからどのくらいのフレームがたったか

	bool  normalFlag_;                      //法線を調べるかどうか

	///////////////カメラ///////////////////

	////変数

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

	///////////////当たり判定///////////////////

	////変数

	Stage* pstage_;                           //ステージクラスのポインタ
	int      hGroundModel_;                   //ステージのモデル番号を入れる変数

	////2Dの際のブロックとの当たり判定に使う

	enum BlockHitTest2D						  
	{
		Right = 0,                            //右
		Left,                                 //左
		Under,                                //下
		Top,                                  //上
	};

public:

	/// <summary>
	/// Playerの状態を表す変数
	/// </summary>
	PlayerStateManager* pState_;

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

	/// <summary>
	/// カメラの処理
	/// </summary>
	void CameraBehavior();

	/// <summary>
	/// 真下の法線を調べてキャラの上軸を決定する
	/// </summary>
	void CheckUnderNormal();

	/// <summary>
	/// ステージに合わせてPlayerを回転する(3D用)
	/// </summary>
	void RotationInStage();

	/// <summary>
	/// ステージに合わせてPlayerを回転する(2D用)
	/// </summary>
	void RotationInStage2D();

	/// <summary>
	/// レイで当たり判定(3D用)
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// レイで当たり判定(2D用)
	/// </summary>
	void StageRayCast2D();

	/// <summary>
	/// 当たり判定(3D用)
	/// </summary>
	/// <param name="data"></param>
	/// <param name="dir">当たり判定する方向</param>
	void HitTest(RayCastData* data, const XMVECTOR& dir);

	/// <summary>
	/// 当たり判定(2D用)
	/// </summary>
	/// <param name="data"></param>
	/// <param name="dir">当たり判定する方向</param>
	void HitTest2D(RayCastData* data,const XMVECTOR& dir);

	/// <summary>
	/// プレイヤー操作(3D用)
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// プレイヤー操作(2D用)
	/// </summary>
	void MovingOperation2D();

	/// <summary>
	/// 指定した時間で呼ばれるメソッド
	/// </summary>
	void TimeMethod() override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="pTarget">当たった相手のポインタ</param>
	void OnCollision(GameObject* pTarget) override;

	/////////////////////セットゲット関数//////////////////////

	/// <summary>
	/// Playerを真逆の状態に設定(まったく反対に設定すると外積が０になってしまうので少しずらす)
	/// </summary>
	void SetInverseNormalAndDown() { vNormal_ += {0, 0.1f, 0, 0}; vNormal_ = -vNormal_;down_ = -vNormal_; }

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
	/// キャラの下のステージの法線をゲット
	/// </summary>
	/// <returns>ステージの法線</returns>
	XMVECTOR GetNormal() { return vNormal_; }

	/// <summary>
	/// キャラの上軸ゲット
	/// </summary>
	/// <returns>キャラの上軸</returns>
	XMVECTOR GetUp() { return up_; }

	/// <summary>
	/// キャラの上軸の角度をゲット
	/// </summary>
	/// <returns>キャラの上軸の角度</returns>
	float GetAngle() { return angle_; }

	/// <summary>
	/// キャラの上軸の角度をセットする
	/// </summary>
	/// <param name="angle">セットしたい角度</param>
	void SetAngle(const float& angle) { angle_ = angle; }

	/// <summary>
	/// 重力をセット
	/// </summary>
	/// <param name="acceleration">セットしたい重力の値</param>
	void SetAcceleration(const float& acceleration) { acceleration_ = acceleration; }

	/// <summary>
	/// Playerのモデル番号をゲット
	/// </summary>
	/// <returns>Playerのモデル番号</returns>
	int GetPlayerhModel() { return hModel_; }

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
	/// Playerの回転マトリクスゲット
	/// </summary>
	/// <returns>Playerの回転マトリクス</returns>
	XMMATRIX GetmmRotate() { return transform_.mmRotate_; }

	/// <summary>
	/// Playerの下ベクトルゲット
	/// </summary>
	/// <returns>Playerの下ベクトル</returns>
	XMVECTOR GetDown() { return down_; }

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
	/// アニメーションするかどうかセット
	/// </summary>
	/// <param name="flag">trueならアニメーションする,falseならアニメーションしない</param>
	void SetAnimFlag(const bool& flag) { Model::SetAnimFlag(hModel_,flag); }

	/// <summary>
	/// カメラのアングル近距離にセット
	/// </summary>
	void SetCamShort() { camStatus_ = SHORT; CameraBehavior();}

	/// <summary>
	/// カメラのアングル長距離にセット
	/// </summary>
	void SetCamLong() { camStatus_ = LONG; CameraBehavior(); }
};

