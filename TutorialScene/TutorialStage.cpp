#include "TutorialStage.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ImGuiSet.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"

//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
	: GameObject(parent, "TutorialStage"), status_(first), spaceModel_(-1),CirclePolyModel_(-1)
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

	//Space���f���̖��邳�ݒ�
	Model::SetBrightness(spaceModel_,0.5);

	//�����ɐݒ�
	Model::SetAlpha(CirclePolyModel_, 0);

	//��p
	Camera::SetFieldAngle(45);

	//���C�g�̋���
	Light::SetIntensity(3);

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
		if ((*i)->GetPosition().x + 1 > pos->x &&
			(*i)->GetPosition().x - 1 < pos->x &&
			(*i)->GetPosition().y - 1 < pos->y &&
			(*i)->GetPosition().y + 1 > pos->y &&
			(*i)->GetPosition().z - 1 < pos->z &&
			(*i)->GetPosition().z + 1 > pos->z)
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
				
				(*i)->SetPosition((*i)->GetPosition().x, pos->y + 2.5, (*i)->GetPosition().z);
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
