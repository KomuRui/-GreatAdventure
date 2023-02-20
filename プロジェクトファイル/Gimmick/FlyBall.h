#pragma once
#include "../Mob.h"
#include "../Engine/Component/Posture.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// ボスシーンに登場してくるPlayerが飛ばして攻撃するためのギミック
/// </summary>
class FlyBall : public Mob
{
	int hStickModel_;     //FlyBallの棒のモデル番号
	Transform tStick_;    //棒用のトランスフォーム
	
	bool isFly_;          //飛んでいるかどうか
	bool isReturnPos;     //元いたポジションに戻っているかどうか

	float rotateAngle_;   //回転するときの角度

	EasingMove* pEasing_; //イージングで移動する時に必要な変数

	XMFLOAT3 beforePos_;  //移動前の位置
	XMFLOAT3 basePos_;    //ベースの位置

	XMVECTOR baseUp_;     //ベースの上ベクトル

public:

	//コンストラクタ
	FlyBall(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一度だけ呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	//////////////////////////////関数//////////////////////////////

	/// <summary>
	/// 飛ぶ
	/// </summary>
	void Fly();

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();

	/// <summary>
	/// 棒のトランスフォームの計算
	/// </summary>
	void StickCalculation();
};

