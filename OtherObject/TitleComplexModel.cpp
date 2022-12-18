#include "TitleComplexModel.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

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

	//�^�C�g����ʂȂǕ\�����邽�߂ɐ�Ƀt�@�C�����[�h���Ă���
	pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene2.txt");
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void TitleComplexModel::StartUpdate()
{
}

//�X�V
void TitleComplexModel::Update()
{
	//y���̃|�W�V���������X�ɉ����Ă���
	transform_.position_.y -= SPEED;

	//y��-20��艺�ɗ�������
	if (transform_.position_.y < LIMIT_Y)
	{
		//�J�����U��
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//�^�C�g���Ȃǂ�\��
		pCreateStage->LoadFileBasedCreateStage();

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
