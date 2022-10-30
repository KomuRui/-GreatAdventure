#include "Mob.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string modelPath)
	: GameObject(parent, "Mob"), hModel_(-1), ModelNamePath_(modelPath)
{

}

//������
void Mob::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= 0);
	

	ChildInitialize();
}

//�X�V�̑O�Ɉ�񂾂��Ă΂��֐�
void Mob::StartUpdate()
{
	ChildStartUpdate();
}

//�X�V
void Mob::Update()
{
	//�p���悲�Ƃɓ�����ς����
	UpdateMove();
}

//�`��
void Mob::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ChildDraw();
}

//�J��
void Mob::Release()
{
}

void Mob::UpdateMove()
{
}

void Mob::ChildInitialize()
{
}

void Mob::ChildDraw()
{
}

void Mob::ChildStartUpdate()
{
}


void Coin::UpdateMove()
{
	transform_.rotate_.y += 4;
}

void Coin::ChildStartUpdate()
{
	Model::SetRayFlag(hModel_, false);
}
