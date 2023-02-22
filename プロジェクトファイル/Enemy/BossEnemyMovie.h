#pragma once
#include "../Mob.h"

/// <summary>
/// 動画用のボスの敵
/// </summary>
class BossEnemyMovie : public Mob
{

public:

	//コンストラクタ
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void ChildInitialize() override;

	//更新の前に一回呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;
};

