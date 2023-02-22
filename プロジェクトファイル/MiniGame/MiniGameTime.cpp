#include "MiniGameTime.h"
#include "../Engine/Global.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const int START_MAX_COUNT = 4;      			//スタートカウントの最大値
	static const float TEXT_INTERVAL = -0.06f;		    //文字の間隔
	static const float NORMAL_START_COUNT_SCALE = 5.0f; //スタートカウント文字の拡大率
}

//コンストラクタ
MiniGameTime::MiniGameTime()
	:pTimeText_(new Text), pStartCountText_(new Text), startCount_(ZERO), startCountTextScale_(ZERO), timerhNum_(ZERO)
{
}

//初期化
void MiniGameTime::Initialize()
{
	//タイマー作成
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());

	//文字の初期化
	pTimeText_->Initialize(TEXT_INTERVAL);
	pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//スタートカウントの初期化
	ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT);
	ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

}

//制限時間描画
void MiniGameTime::LimitTimeDraw()
{
	//ワイド文字列格納用
	wchar_t wtext[FILENAME_MAX];
	std::string text;

	if (Time::GetTimef(timerhNum_) < 30.0f)
	{
		//10秒以上なら
		if (Time::GetTimef(timerhNum_) / 10.0f >= ZERO)
			text = float_to_string(Time::GetTimef(timerhNum_), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(timerhNum_), 3) + "/30.000";
	}
	else
	{
		//表示するタイムを固定
	    ARGUMENT_INITIALIZE(text,"30.000/30.000");

		//ミニゲーム終了する
		MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::END);

		//フェードのステータスがFADE_OUT状態じゃなかったら
		if (GameManager::GetFadeStatus() != FADE_CIRCLE_OUT)
			GameManager::SetFadeStatus(FADE_CIRCLE_OUT, "Image/Fade/BaseFade.png");

		//タイムをロックする
		Time::Lock(timerhNum_);
	}

	//ワイド文字列に変換
	size_t ret;
	setlocale(LC_ALL, ".932");
	mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

	//時間描画
	pTimeText_->Draw(100, 150, wtext, 1.0f, TEXT_INTERVAL);
}

//スタートカウント描画
void MiniGameTime::StartCountDraw()
{
	//もしロックされているのならロック解除
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//一つ前保存
	int beforStartCount = startCount_;

	//startCount_を求める
	ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT - Time::GetTimei(timerhNum_));

	//前回と違うのなら拡大率元に戻す
	if (beforStartCount != startCount_) ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);


	//startCount_が0なら
	if (startCount_ == ZERO)
	{
		//Start描画
		pTimeText_->Draw(460, 440, L"START", 3.0f, -0.15f);
	}
	//マイナスなら開始
	else if (startCount_ < ZERO)
	{
		//ミニゲーム開始する
		MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::PLAY);

		//タイムリセット
		Time::Reset(timerhNum_);
	}
	//startCount_が3以下なら数字描画
	else if (startCount_ <= 3)
	{
		//拡大率を小さくしていく
		startCountTextScale_ -= 0.05f;

		//描画
		pStartCountText_->NumberDraw(960, 440, startCount_, startCountTextScale_);
	}
}
