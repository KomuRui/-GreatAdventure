#include "TitleModelPrincess.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
TitleModelPrincess::TitleModelPrincess(GameObject* parent)
	:GameObject(parent, "TitleModelPrincess"), hModel_(-1)
{
}

//������
void TitleModelPrincess::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("Star_Main_Character2.fbx");
	assert(hModel_ >= ZERO);

	//�A�j���[�V����
	Model::SetAnimFlag(hModel_, true);
	Model::SetAnimFrame(hModel_, 1, 60, 1.0f);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModelPrincess::StartUpdate()
{
}

//�X�V
void TitleModelPrincess::Update()
{
}

//�`��
void TitleModelPrincess::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModelPrincess::Release()
{
}
