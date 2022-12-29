#include "CoinManager.h"
#include "../../Engine/Transform.h"
#include "../../Engine/Text.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

/// <summary>
/// Playerの持ってるコイン管理
/// </summary>
namespace CoinManager
{
	///////////////////////////////変数//////////////////////////////////

	//コインの総数
	int coinTotalCount;

	//画像
	int coinImageNum;               //コインの画像番号
	int crossImageNum;              //×UIの画像番号
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
		coinImageNum = Image::Load("Image/Coin/Coin.png");
		crossImageNum = Image::Load("Image/Coin/Cross.png");

		//テキストの初期化
		ARGUMENT_INITIALIZE(pCoinText_, new Text);
		pCoinText_->Initialize();

		//画像のポジション設定
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "coinImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(coinImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "coinImageY", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.x, GetPrivateProfilefloat("POSITION", "crossImageX", "1", "Image/Coin/CoinPosition.ini"));
		ARGUMENT_INITIALIZE(crossImageTransform_.position_.y, GetPrivateProfilefloat("POSITION", "crossImageY", "1", "Image/Coin/CoinPosition.ini"));

		//テキストのポジション設定
		ARGUMENT_INITIALIZE(textPositiom_.x, GetPrivateProfilefloat("POSITION", "coinTextX", "1", "Image/Coin/CoinPosition.ini"))
		ARGUMENT_INITIALIZE(textPositiom_.y, GetPrivateProfilefloat("POSITION", "coinTextY", "1", "Image/Coin/CoinPosition.ini"))
	}

	//コイン何枚持っているか描画
	void CoinManager::Draw()
	{
		//画像
		Image::SetTransform(coinImageNum, coinImageTransform_);
		Image::Draw(coinImageNum);
		//Image::SetTransform(crossImageNum, crossImageTransform_);
		//Image::Draw(crossImageNum);

		//テキスト
		pCoinText_->Draw(textPositiom_.x, textPositiom_.y, coinTotalCount, coinImageTransform_.scale_.x);
	}


	//コインの追加
	void AddCoin(int num){ coinTotalCount += num; }
}