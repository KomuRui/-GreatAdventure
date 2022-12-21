#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(Stop)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

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

	//Move��ԂȂ�
	if (status_ == Move)
		NextPositionToMove();
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

/////////////////////�֐�//////////////////////

//���̈ʒu�ֈړ�
void UserPlanetBase::NextPositionToMove()
{
	//��Ԃ��Ȃ���ړI�̃|�W�V�����܂ŕύX���Ă���
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&nextPos_), 0.1));
	
	//������0.05��菬�����Ȃ�Stop��Ԃɐݒ�
	if (RangeCalculation(transform_.position_, nextPos_) < 0.05)
	{
		//���g�̃|�W�V���������̈ʒu�ɐݒ�
		ARGUMENT_INITIALIZE(transform_.position_, nextPos_);
		ARGUMENT_INITIALIZE(status_, Stop);
	}

}

//���̃|�W�V�����Z�b�g
void UserPlanetBase::SetNextPosition(const XMFLOAT3& nextPos)
{
	ARGUMENT_INITIALIZE(nextPos_, nextPos); //���̈ʒu�ݒ�
	ARGUMENT_INITIALIZE(status_, Move);     //��Ԑݒ�
}