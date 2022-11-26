#include "GameManager.h"

namespace GameManager
{
	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }
}