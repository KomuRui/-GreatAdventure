#pragma once
#include "../Mob.h"
#include "../Engine/Component/Posture.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// ボスシーンに登場してくるPlayerが飛ばして攻撃するためのギミック
/// </summary>
class FlyBall : public Mob
{
	//飛んでいるかどうか
	bool isFly_;

	//元いたポジションに戻っているかどうか
	bool isReturnPos;

	//回転するときの角度
	float rotateAngle_;

	//イージングで移動する時に必要な変数
	EasingMove* pEasing_;

	//ベースの位置
	XMFLOAT3 basePos_;

public:

	//コンストラクタ
	FlyBall(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一度だけ呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//////////////////////////////関数//////////////////////////////

	/// <summary>
	/// 飛ぶ
	/// </summary>
	void Fly();
};

