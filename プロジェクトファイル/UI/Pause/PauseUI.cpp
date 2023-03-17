#include "PauseUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
PauseUI::PauseUI()
	:pCreateUI_(new CreateStage), isDrawUI_(false)
{}

//描画
void PauseUI::Draw()
{
	//作成したUIの描画を呼ぶ
	pCreateUI_->AllCreateStageDraw();
}

//UI作成
void PauseUI::CreateUI()
{
	//各UI作成
	pCreateUI_->LoadFileCreateStage(nullptr, "Image/Pause/UIInformation/PauseUI.txt");

	//描画しているに変更
	ARGUMENT_INITIALIZE(isDrawUI_, true);
}

//全て削除
void PauseUI::AllRelease()
{
	//削除
	pCreateUI_->AllCreateStageDelete();

	//描画していないに変更
	ARGUMENT_INITIALIZE(isDrawUI_, true);
}