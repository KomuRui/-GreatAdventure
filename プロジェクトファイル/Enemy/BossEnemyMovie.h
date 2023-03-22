#pragma once
#include "../Mob/Mob.h"
#include "../UI/TalkImage.h"

/// <summary>
/// 動画用のボスの敵
/// </summary>
class BossEnemyMovie : public Mob
{
	//話す画像
	TalkImage* pTalkImage_;

	//音楽
	int hAudio_;

	//加算する値
	float addScaleValue_;

	//会話を変更しているか
	bool isChangeTalk_;

public:

	//コンストラクタ
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	//デストラクタ
	~BossEnemyMovie();

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新
	void ChildUpdate() override;

	/////////////////////関数//////////////////////

	//拡大する
	void AddScale();
};

