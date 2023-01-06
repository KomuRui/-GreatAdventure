#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

////�萔
namespace
{
	static const float ROTATION_SPEED = 0.1f;			 //��]���x
	static const float STATUS_CHANGE_DISTANCE = 0.05f;   //��Ԃ��ύX����Ƃ��̋���
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //��ԌW��
}

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
	transform_.rotate_.y += ROTATION_SPEED;

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
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&nextPos_), INTERPOLATION_COEFFICIENT));
	
	//������0.05��菬�����Ȃ�Stop��Ԃɐݒ�
	if (RangeCalculation(transform_.position_, nextPos_) < STATUS_CHANGE_DISTANCE)
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