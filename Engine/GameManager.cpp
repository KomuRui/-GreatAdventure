#include "GameManager.h"

namespace GameManager
{
	///////////////////////////////変数//////////////////////////////////
	
	//現在使用されているプレイヤーのポインタ格納用
	Player* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	///////////////////////////////セットゲット関数//////////////////////////////////
	
	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	///////////////////////////////フェード用関数////////////////////////////////////

	//フェード描画
	void FadeDraw() {};

	//フェードイン描画
	void FadeInDraw() {};

	//フェードアウト描画
	void FadeOutDraw(){};
}