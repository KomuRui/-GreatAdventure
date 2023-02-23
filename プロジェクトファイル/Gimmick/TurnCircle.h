#pragma once
#include "../Mob/Mob.h"
#include "../Engine/Component/Posture.h"

/// <summary>
/// ミニゲームの登場するギミックの回る円
/// </summary>
class TurnCircle : public Mob
{
	//正しい姿勢にしてくれるコンポーネント
	Posture posture_;

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

};

