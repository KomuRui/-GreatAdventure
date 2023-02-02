#include "UserSelectNewFileUI.h"
#include "../Engine/CreateStage.h"
#include "../Engine/Easing.h"

//�R���X�g���N�^
UserSelectNewFileUI::UserSelectNewFileUI(GameObject* parent)
	: GameObject(parent, "UserSelectNewFileUI"), isPush_(false)
{
}

//������
void UserSelectNewFileUI::Initialize()
{
	////////////////////////////////transform////////////////////////////////////

	transform_.position_.x = 2;
	Time::UnLock();

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
	if(isPush_)
		transform_.position_ = VectorToFloat3(XMVectorLerp(XMVectorSet(0, 0, 0, 0), XMVectorSet(-2, 0, 0, 0), Easing::InQuart(Time::GetTimef() / 2.0f)));
	else
	    transform_.position_ = VectorToFloat3(XMVectorLerp(XMVectorSet(2, 0, 0, 0),XMVectorSet(0,0,0,0),Easing::OutQuart(Time::GetTimef() / 2.0f)));
}

//�`��
void UserSelectNewFileUI::Draw()
{

}

//���
void UserSelectNewFileUI::Release()
{
}
