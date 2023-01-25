#include "MiniGameManager.h"
#include "../../Engine/Global.h"
#include "../../Engine/Text.h"
#include <locale.h>

//ミニゲームの管理をする
namespace MiniGameManager
{
	//ミニゲームの状態
	MiniGameStatus miniGameStatus_;   

	//結果表示するための変数
	Text* pResultTimeText_;      //結果を文字で表示するための変数     
	int resultDis_;              //最終的な結果(距離)

	//初期化
	void Initialize()
	{
		//開始していないに初期化
		ARGUMENT_INITIALIZE(miniGameStatus_, MiniGameStatus::NOT_START);

		//距離初期化
		ARGUMENT_INITIALIZE(resultDis_, ZERO);
	}

	//描画
	void Draw()
	{
		switch (miniGameStatus_)
		{
			//まだ開始していない
		case MiniGameStatus::NOT_START:
			StartCountDraw();
			break;
			//ゲーム中
		case MiniGameStatus::PLAY:
			LimitTimeDraw();
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