#pragma once
#include "../Mob/Mob.h"
#include "../UI/TalkImage.h"

/// <summary>
/// 最後のシーンのプリンセス
/// </summary>
class Princess : public Mob
{
	//表示させた画像のクラスを保存しておく用
	TalkImage* pTalkImage_;

public:

	//コンストラクタ
	Princess(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

};

