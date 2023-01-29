#pragma once
#include "PlayerBase.h"

/// <summary>
/// MiniGame用のPlayer
/// </summary>
class PlayerMiniGame : public PlayerBase
{

	int   hPictWind_;     //風の画像番号
	int   hPictWind2_;    //風の画像番号2

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	PlayerMiniGame(GameObject* parent);


	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildPlayerInitialize() override;

	//スタートアップデート
    void ChildPlayerStartUpdate() override;

	//更新
	void ChildPlayerUpdate() override;

	//描画
	void ChildDraw() override;

	//ステージに合わせて回転
	void RotationInStage() override;

	//Playerのカメラの処理
	void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	/////////////////////////関数//////////////////////////

	/// <summary>
	/// プレイヤー操作
	/// </summary>
	void MovingOperation();

	/// <summary>
	/// レイで当たり判定
	/// </summary>
	void StageRayCast();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="data">レイキャストのデータ</param>
	/// <param name="dir">当たり判定する方向</param>
	void HitTest(RayCastData* data, const XMVECTOR& dir);

	/// <summary>
	/// ランモードの時のカメラの処理
	/// </summary>
	void RunModeCameraBehavior();

};

