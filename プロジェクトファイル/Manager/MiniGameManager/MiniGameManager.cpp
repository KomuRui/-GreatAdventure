#include "MiniGameManager.h"
#include "../../Engine/Global.h"
#include "../../Engine/Text.h"
#include "../../MiniGame/MiniGameTime.h"
#include "../../MiniGame/Combo.h"
#include <locale.h>

//定数
namespace
{
	static const float TEXT_INTERVAL = -0.06f;		    //文字の間隔
}

//ミニゲームの管理をする
namespace MiniGameManager
{
	//ミニゲームの状態
	MiniGameStatus miniGameStatus_;   

	//ミニゲームの時間など表示する
	MiniGameTime* miniGameTime_;

	//コンボ表示
	Combo* combo_;

	//結果表示するための変数
	Text* pResultTimeText_;      //結果を文字で表示するための変数     
	int resultDis_;              //最終的な結果(距離)

	//初期化
	void Initialize()
	{
		//文字の初期化
		ARGUMENT_INITIALIZE(pResultTimeText_, new Text);
		pResultTimeText_->Initialize(TEXT_INTERVAL);

		//初期化
		ARGUMENT_INITIALIZE(miniGameTime_, new MiniGameTime);
		ARGUMENT_INITIALIZE(combo_, new Combo);

		//開始していないに初期化
		ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::NOT_START);

		//距離初期化
		ARGUMENT_INITIALIZE(resultDis_, ZERO);
	}

	//描画
	void Draw()
	{
		//コンボ表示
		combo_->Draw();

		//ミニゲームの状態によって表示する物を変える
		switch (miniGameStatus_)
		{
			//まだ開始していない
		case MiniGameStatus::NOT_START:
			miniGameTime_->StartCountDraw();
			break;
			//ゲーム中
		case MiniGameStatus::PLAY:
			miniGameTime_->LimitTimeDraw();
			break;
			//終わり
		case MiniGameStatus::END:
			ResultDraw();
			break;

		default:
			break;
		}

	}

	//結果表示
	void MiniGameManager::ResultDraw()
	{
		//ワイド文字列格納用
		wchar_t wtext[FILENAME_MAX];
		std::string text = std::to_string(resultDis_) + "m";

		//ワイド文字列に変換
		size_t ret;
		setlocale(LC_ALL, ".932");
		mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

		//結果描画
		pResultTimeText_->Draw(760, 540, wtext, 2.5f, -0.15f);
	}

	//開始しているかをセット
	void ChangeMiniGameStatus(MiniGameStatus status) { miniGameStatus_ = status; }

	//ミニゲームの状態をゲット
	MiniGameStatus  MiniGameManager::GetMiniGameStatus() { return miniGameStatus_; }

	//開始しているか
	bool MiniGameManager::IsPlay() { return (miniGameStatus_ == MiniGameStatus::PLAY); }

	//距離を設定
	void SetResultDis(const int& dis) { resultDis_ = dis; }

}