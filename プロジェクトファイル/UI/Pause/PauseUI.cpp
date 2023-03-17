#include "PauseUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//コンストラクタ
PauseUI::PauseUI(GameObject* parent)
	:GameObject(parent,"PauseUI")
{}

//初期化
void PauseUI::Initialize()
{
	//各UI作成
	CreateStage* pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Image/Pause/UIInformation/PauseUI.txt");
}
