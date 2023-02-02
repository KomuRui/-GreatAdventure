#include "UserSelectNewFileUI.h"
#include "../Engine/CreateStage.h"

//�R���X�g���N�^
UserSelectNewFileUI::UserSelectNewFileUI(GameObject* parent)
	: GameObject(parent, "UserSelectNewFileUI")
{
}

//������
void UserSelectNewFileUI::Initialize()
{
	////////////////////////////////transform////////////////////////////////////

	transform_.position_.x = -10;

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserSelectNewFileUI.txt");
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void UserSelectNewFileUI::StartUpdate()
{
}

//�X�V
void UserSelectNewFileUI::Update()
{
}

//�`��
void UserSelectNewFileUI::Draw()
{

}

//���
void UserSelectNewFileUI::Release()
{
}
