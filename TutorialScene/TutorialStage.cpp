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
		"Stage/First/first_2.fbx",
		"first_Stage.fbx",
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}


	////////////////Circleflag_�̏�����//////////////////

	//���̂��g���Ă���Ȃ�flag��true�ɂ��Ă���
	Circleflag_[first] = false;
	Circleflag_[Two] = false;
	Circleflag_[Three] = true;

	///////////////transform///////////////////

	//�X�e�[�W���Ƃɏ����ʒu�ݒ�

	//1
	pos_[first] = { 2,2,0 };

	//2
	pos_[Two] = { 2,2,0 };

	//3
	pos_[Three] = { 20,15,0 };
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
