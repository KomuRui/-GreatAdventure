#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath)
{
}

//������
void UserPlanetBase::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void UserPlanetBase::StartUpdate()
{
}

//�X�V
void UserPlanetBase::Update()
{
	//������]������
	transform_.rotate_.y += RATATION_SPEED;
}

//�`��
void UserPlanetBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void UserPlanetBase::Release()
{
}
