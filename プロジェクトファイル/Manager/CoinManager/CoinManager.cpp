#include "CoinManager.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"
#include "../../Engine/Global.h"
#include "../../Engine/Sprite.h"

/// <summary>
/// Playerの持ってるコイン管理
/// </summary>
namespace CoinManager
{
	///////////////////////////////変数//////////////////////////////////

	//コインの総数
	int coinTotalCount;

	//画像
	Sprite* pCoinImage;             //コインの画像
	Sprite* pCrossImage;            //×UIの画像
	Transform coinImageTransform_;  //コイン画像の位置・拡大率
	Transform crossImageTransform_; //×画像の位置・拡大率

	//テキスト
	Text* pCoinText_;           //コインの数表示するテキスト
	XMFLOAT2 textPositiom_;     //テキストのポジション

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void CoinManager::Initialize()
	{
		//コインの総数初期化
		ARGUMENT_INITIALIZE(coinTotalCount, ZERO);

		//画像のロード
		ARGUMENT_INITIALIZE(pCoinImage, new Sprite);
		ARGUMENT_INITIALIZE(pCrossImage, new Sprite);
		pCoinImage->Load("Image/Coin/Coin.png");
		pCrossImage->Load("Image/Coin/Cross.png");

		//テキストの初期化
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize("Text/NumberFont.png", 128, 256, 10);

		//画像のポジション設定
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "coinImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "coinImageY", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "crossImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "crossImageY", "1", "Image/Coin/CoinPosition.ini"));

		//テキストのポジション設定
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "coinTextX", "1", "Image/Coin/CoinPosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "coinTextY", "1", "Image/Coin/CoinPosition.ini"))
	}

	//シーン遷移の時の初期化
	void CoinManager::SceneTransitionInitialize()
	{
		//テキストの初期化
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize("Text/NumberFont.png", 128, 256, 10);
	}

	//コイン何枚持っているか描画
	void CoinManager::Draw()
	{
		//画像
		{
			//テクスチャのサイズ取得
			XMFLOAT3 size = pCoinImage->GetTextureSize();

			//切り抜き範囲をリセット（画像全体を表示する）
			RECT rect;
			rect.left = ZERO;
			rect.top = ZERO;
			rect.right = (long)size.x;
			rect.bottom = (long)size.y;

			//描画
			pCoinImage->Draw(coinImageTransform_, rect);
		}

		//テキスト
		{
			pCoinText_->NumberDraw(textPositiom_.x, textPositiom_.y, coinTotalCount, coinImageTransform_.scale_.x);
		}
	}


	//コインの追加
	void AddCoin(int num){ coinTotalCount += num; }
}