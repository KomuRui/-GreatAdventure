#include "TitleModel.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
TitleModel::TitleModel(GameObject* parent)
	:GameObject(parent,"TitleModel"),hModel_(-1)
{
}

//������
void TitleModel::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("TitleModel.fbx");
	assert(hModel_ >= 0);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleModel::StartUpdate()
{
}

//�X�V
void TitleModel::Update()
{
}

//�`��
void TitleModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleModel::Release()
{
}
