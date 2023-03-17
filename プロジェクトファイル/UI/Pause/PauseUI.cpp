#include "PauseUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
PauseUI::PauseUI(GameObject* parent)
	:GameObject(parent,"PauseUI")
{}

//������
void PauseUI::Initialize()
{
	//�eUI�쐬
	CreateStage* pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Image/Pause/UIInformation/PauseUI.txt");
}
