#pragma once
#include "../Mob.h"

/// <summary>
/// ミニゲームの登場するギミックの回る円
/// </summary>
class TurnCircle : public Mob
{

	//回転角度
	float rotationAngle_;

public:

	//コンストラクタ
	TurnCircle(GameObject * parent);

	/////////////////////オーバーライドする関数//////////////////////

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;

	/////////////////////関数//////////////////////

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();

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

};

