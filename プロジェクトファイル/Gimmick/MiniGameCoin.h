#pragma once
#include "Coin.h"
#include "../Engine/Component/Posture.h"

/// <summary>
/// ミニゲーム用のコイン
/// </summary>
class MiniGameCoin : public Coin
{
	//正しい姿勢にしてくれるコンポーネント
	Posture posture_;

public:

	//コンストラクタ
	MiniGameCoin(GameObject* parent);


	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一度だけ呼ばれる関数
	void ChildCoinStartUpdate() override;

	//更新
	void ChildCoinUpdate() override;

};

