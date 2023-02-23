#include "MovieCoin.h"
#include "../../Enemy/BossEnemyMovie.h"
#include "../../Player/PlayerMovie.h"
#include "../../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Easing.h"

//コンストラクタ
MovieCoin::MovieCoin(GameObject* parent)
	:Coin(parent, "MovieCoin"),isChange_(false)
{
}

//更新の前に一度だけ呼ばれる関数
void MovieCoin::ChildCoinStartUpdate()
{
	//目的地のポジション取得
	ARGUMENT_INITIALIZE(destinationPos_,((BossEnemyMovie*)FindObject("BossEnemyMovie"))->GetPosition());

	//最初に移動するポジションを求める
	PlayerMovie* pPlayer = ((PlayerMovie*)FindObject("Player"));
	XMFLOAT3 NextPos = Float3Add(pPlayer->GetPosition(), VectorToFloat3(pPlayer->GetNormal() * 6.0f));

	//イージングの情報設定
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.position_, transform_.position_, NextPos, 1.0f, Easing::InOutQuart));

	//明るさ
	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void MovieCoin::ChildCoinUpdate()
{
	//移動完了したら
	if (pEasing_->Move())
	{
		//チェンジしていたら
		if (isChange_)
		{
			//ヒットエフェクト
			CoinEffectManager::HitEffect();

			//削除
			KillMe();
		}
		else
		{
			//次のイージングの情報設定
			pEasing_->Reset(&transform_.position_, transform_.position_, destinationPos_, 1.0f, Easing::InOutQuart);

			//チェンジしたにする
			ARGUMENT_INITIALIZE(isChange_, true);
		}
	}
}
