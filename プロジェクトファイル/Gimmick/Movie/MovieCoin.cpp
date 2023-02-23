#include "MovieCoin.h"
#include "../../Enemy/BossEnemyMovie.h"
#include "../../Player/PlayerMovie.h"
#include "../../Manager/EffectManager/CoinEffectManager/CoinEffectManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Easing.h"

//定数
namespace
{
	static const float EASING_TIME = 1.0f;				//イージングするために必要な時間
	static const float FIRST_MOVE_VALUE_RATIO = 6.0f;   //1回目の移動時の値の倍率
	static const float SECOND_MOVE_VALUE_RATIO = 3.0f;  //2回目の移動時の値の倍率
}

//コンストラクタ
MovieCoin::MovieCoin(GameObject* parent)
	:Coin(parent, "MovieCoin"),isChange_(false)
{
}

//更新の前に一度だけ呼ばれる関数
void MovieCoin::ChildCoinStartUpdate()
{
	//目的地のポジション求める
	BossEnemyMovie* pBoss = (BossEnemyMovie*)FindObject("BossEnemyMovie");
	ARGUMENT_INITIALIZE(destinationPos_, Float3Add(pBoss->GetPosition(), VectorToFloat3(pBoss->GetNormal() * SECOND_MOVE_VALUE_RATIO)));

	//最初に移動するポジション求める
	PlayerMovie* pPlayer = ((PlayerMovie*)FindObject("Player"));
	XMFLOAT3 NextPos = Float3Add(pPlayer->GetPosition(), VectorToFloat3(pPlayer->GetNormal() * FIRST_MOVE_VALUE_RATIO));

	//イージングの情報設定
	ARGUMENT_INITIALIZE(pEasing_,new EasingMove(&transform_.position_, transform_.position_, NextPos, EASING_TIME, Easing::InOutQuart));

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
			pEasing_->Reset(&transform_.position_, transform_.position_, destinationPos_, EASING_TIME, Easing::InOutQuart);

			//チェンジしたにする
			ARGUMENT_INITIALIZE(isChange_, true);
		}
	}
}
