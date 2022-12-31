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

	//話すかどうか
	bool isTalk_;

public:

	//コンストラクタ
	MainMob(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//描画
	void ChildDraw() override;

	/// <summary>
	/// Playerの方を向く
	/// </summary>
	void LookPlayer();

	/// <summary>
	/// 話すかどうかをセット
	/// </summary>
	/// <param name="flag">trueなら話す,falseなら話さない</param>
	void SetTalk(const bool& flag) { isTalk_ = flag; }
};
