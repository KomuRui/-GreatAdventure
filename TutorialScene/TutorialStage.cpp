#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ImGuiSet.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"

//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(Two), spaceModel_(-1),CirclePolyModel_(-1)
{
	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = -1;
		pos_[i] = { 0,0,0 };
	}

	//�X�e�[�W�쐬�̎��̃t�@�C���l�[��������
	StageFileNmae_[first] = "Stage/Tutorial/StageInformation/TutorialStage1.txt";
	StageFileNmae_[Two]   = "Stage/Tutorial/StageInformation/TutorialStage2.txt";

	fieldAngle_[first] = 45;
	fieldAngle_[Two] = 100;

	lightIntensity_[first] = 3;
	lightIntensity_[Two] = 5;
}

//������
void TutorialStage::Initialize()
{
	/////////////////�X�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	//�X�e�[�W�쐬
	ImGuiSet* a = Instantiate<ImGuiSet>(this);
	a->CreateStage(StageFileNmae_[status_]);

	//
	tBlock_ = a->GetTransformBlock();

	///////////////���f���f�[�^�̃��[�h///////////////////

	std::string fileName[] = {
		"Stage/Tutorial/first_1.fbx",
		"Stage/Tutorial/first_Stage1.fbx"
	};

	for (int i = 0; i < MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}

	spaceModel_ = Model::Load("Stage/SpaceModel/Space.fbx");
	CirclePolyModel_ = Model::Load("Stage/Tutorial/first_Stage_Polygon.fbx");

	//////////////////////�e�ڍאݒ�////////////////////////

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(spaceModel_,0.5);

	//�����ɐݒ�
	Model::SetAlpha(CirclePolyModel_, 0);

	//��p
	Camera::SetFieldAngle(fieldAngle_[status_]);

	//���C�g�̋���
	Light::SetIntensity(lightIntensity_[status_]);

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

//�X�V�̑O�Ɉ�񂾂��Ă΂��
void TutorialStage::StartUpdate()
{
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

	Model::SetTransform(spaceModel_, tSpace_);
	Model::Draw(spaceModel_);
}

//�J��
void TutorialStage::Release()
{
}

//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
bool TutorialStage::IsBlock(XMFLOAT3 *pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i)->GetPosition().x + (1 * (*i)->GetScale().x) > pos->x &&
			(*i)->GetPosition().x - (1 * (*i)->GetScale().x) < pos->x &&
			(*i)->GetPosition().y - (1 * (*i)->GetScale().y) < pos->y &&
			(*i)->GetPosition().y + (1 * (*i)->GetScale().y) > pos->y &&
			(*i)->GetPosition().z - (1 * (*i)->GetScale().z) < pos->z &&
			(*i)->GetPosition().z + (1 * (*i)->GetScale().z) > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i)->GetPosition().x + 1.5);
				break;
			case 1:
				pos->x = ((*i)->GetPosition().x - 1.5);
				break;
			case 2:
				pos->y = ((*i)->GetPosition().y + 2);
				break;
			case 3:
				pos->y = ((*i)->GetPosition().y - 2);
				(*i)->SetIsHit(true);
				break;
			}
			
			return true;
		}
	}

	return false;
}

//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
bool TutorialStage::IsBlock3D(XMFLOAT3* pos, XMVECTOR move,XMMATRIX mat, int status)
{
	//for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	//{
	//	//�������x�N�g�����쐬
	//	XMVECTOR v[6] = { { 1,0,0 },{-1,0,0},{0,-1,0},{0,1,0},{0,0,-1},{0,0,1} };
	//	XMFLOAT3 f[6];

	//	//���ׂĉ�]������
	//	for (int i = 0; i < 6; i++)
	//	{
	//		XMStoreFloat3(&f[i],XMVector3TransformCoord(v[i], mat));
	//	}
	//	
	//	if ((*i).position_.x + f[0].x > pos->x &&
	//		(*i).position_.x + f[1].x < pos->x &&
	//		(*i).position_.y + f[2].y < pos->y &&
	//		(*i).position_.y + f[3].y > pos->y &&
	//		(*i).position_.z + f[4].z < pos->z &&
	//		(*i).position_.z + f[5].z > pos->z)
	//	{
	//		switch (status)
	//		{
	//		case 0:
	//			XMStoreFloat3(pos,XMLoadFloat3(&(*i).position_) - (move) * 2);
	//			break;
	//		case 1:
	//			XMStoreFloat3(pos, XMLoadFloat3(&(*i).position_) + (move) * 2);
	//			break;
	//		case 2:
	//			XMStoreFloat3(pos, XMLoadFloat3(&(*i).position_) - (move)*2);
	//			break;
	//		case 3:
	//			XMStoreFloat3(pos, XMLoadFloat3(&(*i).position_) + (move)* 2);
	//			break;
	//		case 4:
	//			XMStoreFloat3(pos, XMLoadFloat3(&(*i).position_) - (move) * 2);
	//			break;
	//		case 5:
	//			XMStoreFloat3(pos, XMLoadFloat3(&(*i).position_) - (move) * 2);
	//			break;
	//		}

	//		return true;
	//	}
	//}

	return false;
}
