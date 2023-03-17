#include "PauseUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"

//�R���X�g���N�^
PauseUI::PauseUI()
	:pCreateUI_(new CreateStage), isDrawUI_(false)
{}

//�`��
void PauseUI::Draw()
{
	//�쐬����UI�̕`����Ă�
	pCreateUI_->AllCreateStageDraw();
}

//UI�쐬
void PauseUI::CreateUI()
{
	//�eUI�쐬
	pCreateUI_->LoadFileCreateStage(nullptr, "Image/Pause/UIInformation/PauseUI.txt");

	//�`�悵�Ă���ɕύX
	ARGUMENT_INITIALIZE(isDrawUI_, true);
}

//�S�č폜
void PauseUI::AllRelease()
{
	//�폜
	pCreateUI_->AllCreateStageDelete();

	//�`�悵�Ă��Ȃ��ɕύX
	ARGUMENT_INITIALIZE(isDrawUI_, true);
}