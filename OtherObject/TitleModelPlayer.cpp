#include "TitleModelPlayer.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
TitleModelPlayer::TitleModelPlayer(GameObject* parent)
	:GameObject(parent, "TitleModelPlayer"), hModel_(-1)
{
}

//������
void TitleModelPlayer::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

	//�A�j���[�V����
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, 1, 60, 1.0f);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModelPlayer::StartUpdate()
{
}

//�X�V
void TitleModelPlayer::Update()
{
}

//�`��
void TitleModelPlayer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModelPlayer::Release()
{
}
