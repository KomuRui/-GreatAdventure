#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"

//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(first)
{
	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = -1;
		pos_[i] = { 0,0,0 };
	}
}

//������
void TutorialStage::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	std::string fileName[] = {
		"Stage/First/first_1.fbx",
		"first_Stage.fbx"
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}


	////////////////Circleflag_�̏�����//////////////////

	//3D�̓��������������Ȃ�flag��true�ɂ��Ă���(2D�Ȃ�false)
	threeDflag_[first] = false;
	threeDflag_[Two] = true;

	///////////////transform///////////////////

	//�X�e�[�W���Ƃ�Player�̏����ʒu�ݒ�

	//1
	pos_[first] = { 2,2,0 };

	//2
	pos_[Two] = { 20,15,0 };

}

//�X�V
void TutorialStage::Update()
{
}

//�`��
void TutorialStage::Draw()
{
	Model::SetTransform(hModel_[status_], transform_);
	Model::Draw(hModel_[status_]);
}

//�J��
void TutorialStage::Release()
{
}

void TutorialStage::StartUpdate()
{
}
