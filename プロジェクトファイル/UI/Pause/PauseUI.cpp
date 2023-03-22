#include "PauseUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/ButtonManager/ButtonManager.h"

//�R���X�g���N�^
PauseUI::PauseUI()
	:pCreateUI_(new CreateStage), isDrawUI_(false)
{}

//�X�V
void PauseUI::Update()
{
	//�쐬����UI�̍X�V���Ă�
	pCreateUI_->AllCreateStageUpdate();
}

//�`��
void PauseUI::Draw()
{
	//�����`�悵�Ă��Ȃ��̂Ȃ�
	if (!isDrawUI_) return;

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
	pCreateUI_->AllCreateStageDelete(false);

	//�{�^�����Z�b�g
	ButtonManager::Reset();

	//�`�悵�Ă��Ȃ��ɕύX
	ARGUMENT_INITIALIZE(isDrawUI_, false);
}