#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ImGuiSet.h"


//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(Two), spaceModel_(-1),CirclePolyModel_(-1)
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

	a->CreateStage("Stage/Tutorial/StageInformation/TutorialStage2.txt");

	tBlock_ = a->GetTransformBlock();

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

	spaceModel_ = Model::Load("Stage/SpaceModel/Space2.fbx");
	CirclePolyModel_ = Model::Load("Stage/Tutorial/first_Stage_Polygon.fbx");

	Model::SetAlpha(CirclePolyModel_, 0);
	Model::SetRayFlag(hModel_[Two], false);
	Model::SetRayFlag(spaceModel_, false);

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
	tSpace_.rotate_.y += 0.2;
}

//�`��
void TutorialStage::Draw()
{
	Model::SetTransform(hModel_[status_], transform_);
	Model::Draw(hModel_[status_]);

	if (status_ == Two)
	{
		Model::SetTransform(CirclePolyModel_, transform_);
		Model::Draw(CirclePolyModel_);
	}

	Model::SetTransform(spaceModel_, tSpace_);
	Model::Draw(spaceModel_);
}

//�J��
void TutorialStage::Release()
{
}

//�X�V�̑O�Ɉ�񂾂��Ă΂��
void TutorialStage::StartUpdate()
{
}

//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
bool TutorialStage::IsBlock(XMFLOAT3 *pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i).position_.x + 1 > pos->x &&
			(*i).position_.x - 1 < pos->x &&
			(*i).position_.y - 1 < pos->y &&
			(*i).position_.y + 1 > pos->y &&
			(*i).position_.z - 1 < pos->z &&
			(*i).position_.z + 1 > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i).position_.x + 1.5);
				break;
			case 1:
				pos->x = ((*i).position_.x - 1.5);
				break;
			case 2:
				pos->y = ((*i).position_.y + 2);
				break;
			case 3:
				pos->y = ((*i).position_.y - 2);
				break;
			}
			
			return true;
		}
	}

	return false;
}

//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
bool TutorialStage::IsBlock3D(XMFLOAT3* pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i).position_.x + 1 > pos->x &&
			(*i).position_.x - 1 < pos->x &&
			(*i).position_.y - 1 < pos->y &&
			(*i).position_.y + 1 > pos->y &&
			(*i).position_.z - 1 < pos->z &&
			(*i).position_.z + 1 > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i).position_.x + 1.5);
				break;
			case 1:
				pos->x = ((*i).position_.x - 1.5);
				break;
			case 2:
				pos->y = ((*i).position_.y + 2);
				break;
			case 3:
				pos->y = ((*i).position_.y - 2);
				break;
			}

			return true;
		}
	}

	return false;
}
