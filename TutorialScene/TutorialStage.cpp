#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ImGuiSet.h"


//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(first), spaceModel_(-1)
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
	ImGuiSet* a = Instantiate<ImGuiSet>(this);

	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage1.txt");

	///////////////���f���f�[�^�̃��[�h///////////////////

	std::string fileName[] = {
		"Stage/Tutorial/first_1.fbx",
		"Stage/Tutorial/first_Stage.fbx"
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}

	//spaceModel_ = Model::Load("Stage/SpaceModel/Space.fbx");
	Model::SetRayFlag(hModel_[Two], false);

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

	/*Model::SetTransform(spaceModel_, transform_);
	Model::Draw(spaceModel_);*/
}

//�J��
void TutorialStage::Release()
{
}

void TutorialStage::StartUpdate()
{
}
