#pragma once
#include "PlayerBase.h"

/// <summary>
/// 3D用のPlayer
/// </summary>
class Player3D : public PlayerBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	Player3D(GameObject* parent);
	Player3D(GameObject* parent, std::string modelPath, std::string name);


	/////////////////////オーバーライドする関数//////////////////////

	//継承先用の更新
	void ChildPlayerUpdate() override;

	//ステージに合わせて回転
	void RotationInStage() override;

	//Playerのカメラの処理
	void PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar) override;

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

};

