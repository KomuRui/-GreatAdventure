#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

/// <summary>
/// メインモブキャラ
/// </summary>
class MainMob : public Mob
{
	//Playerの方を向く行列
	XMMATRIX toPlayer_;

	//一回でもPlayerの方向いたかどうか
	bool isLookPlayer_;

	//アニメーションするかどうか
	bool isAnim_;

public:

	//コンストラクタ
	MainMob(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	/// <summary>
	/// Playerの方を向く
	/// </summary>
	void LookPlayer();

	/// <summary>
	/// アニメーションするかどうかをセット
	/// </summary>
	/// <param name="flag">trueならアニメーションする,falseならしない</param>
	void SetAnim(const bool& flag) { isAnim_ = flag; }
};
