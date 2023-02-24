#pragma once
#include "../Mob/Mob.h"
#include "../UI/TalkImage.h"

/// <summary>
/// 動画用のボスの敵
/// </summary>
class BossEnemyMovie : public Mob
{
	//表示させた画像のクラスを保存しておく用
	TalkImage* pTalkImage_;

	//加算する値
	float addScaleValue_;

public:

	//コンストラクタ
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	/////////////////////関数//////////////////////

	//拡大する
	void AddScale();
};

