#include "UserPlanet.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
UserPlanet::UserPlanet(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath)
{
}

//������
void UserPlanet::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void UserPlanet::StartUpdate()
{
}

//�X�V
void UserPlanet::Update()
{
	//������]������
	transform_.rotate_.y += RATATION_SPEED;
}

//�`��
void UserPlanet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//���
void UserPlanet::Release()
{
}
