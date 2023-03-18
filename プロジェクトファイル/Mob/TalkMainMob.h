#pragma once
#include "../Mob/Mob.h"
#include "../Engine/ResourceManager/Model.h"
#include "../UI/TalkImage.h"

/// <summary>
/// メインモブキャラ
/// </summary>
class TalkMainMob : public Mob
{
	//画像番号
	int hPict_;    

	//音番号
	int hAudio_;

	//画像のトランスフォーム
	Transform tPict_;

	//Playerの方を向く行列
	XMMATRIX toPlayer_;

	//表示させた画像のクラスを保存しておく用
	TalkImage *pTalkImage_;

	//一回でもPlayerの方向いたかどうか
	bool isLookPlayer_;

	//話すかどうか
	bool isTalk_;

public:

	//コンストラクタ
	TalkMainMob(GameObject* parent, std::string modelPath, std::string name);

	//デストラクタ
	~TalkMainMob();

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
	/// 指定距離内に入っているかどうか
	/// </summary>
	bool IsInSpecifiedDistance();
};
