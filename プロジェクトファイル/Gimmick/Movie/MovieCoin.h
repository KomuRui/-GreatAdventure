#pragma once
#include "../Coin.h"
#include "../../Engine/Component/EasingMove.h"

/// <summary>
/// ムービー用のコイン
/// </summary>
class MovieCoin : public Coin
{
	//移動先ポジション
	XMFLOAT3 destinationPos_;

	//イージングで移動するために必要なコンポーネント
	EasingMove* pEasing_;

	//チェンジしているかどうか
	bool isChange_;

public:

	//コンストラクタ
	MovieCoin(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//更新の前に一度だけ呼ばれる関数
	void ChildCoinStartUpdate() override;

	//更新
	void ChildCoinUpdate() override;

};

