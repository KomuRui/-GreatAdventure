#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/CreateStage.h"

//�R���X�g���N�^
TitleComplexModel::TitleComplexModel(GameObject* parent)
	:GameObject(parent, "TitleComplexModel"), hModel_(-1)
{
}

//������
void TitleComplexModel::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load("TitleScene/Model/TitleComplexModel.fbx");
	assert(hModel_ >= ZERO);

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleComplexModel::StartUpdate()
{
}

//�X�V
void TitleComplexModel::Update()
{
	//y���̃|�W�V���������X�ɉ����Ă���
	transform_.position_.y -= 0.1;

	//y��-20��艺�ɗ�������
	if (transform_.position_.y < -20.0f)
	{
		//�J�����U��
		Camera::SetCameraVibration(0.4f);

		//�^�C�g����ʂȂǔz�u
		CreateStage* pCreateStage = new CreateStage;
		pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene2.txt");

		//���g���폜
		KillMe();
	}
}

//�`��
void TitleComplexModel::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void TitleComplexModel::Release()
{
}
