#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

////�萔
namespace
{
	static const float ROTATION_SPEED = 0.1f;			 //��]���x
	static const float STATUS_CHANGE_DISTANCE = 0.05f;   //��Ԃ��ύX����Ƃ��̋���
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //��ԌW��
	static const float FALL_SPEED = 0.4f;                //�����鑬�x�̒l
	static const float KILL_VALUE = -40.0f;              //�폜����Ƃ��̒l
}

//�R���X�g���N�^
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(PlanetStatus::Stop), isSelect_(false)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void UserPlanetBase::Initialize()
{
	//���f���f�[�^���[�h
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//�p����p
	ChildInitialize();
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

	//��Ԃɂ���ČĂԊ֐�������
	switch (status_)
	{
	//�ړ�
	case PlanetStatus::Move:

		NextPositionToMove();
		break;

	//������
	case PlanetStatus::Fall:

		Fall();
		break;

	default:
		break;
	}


	//�p����p
	ChildUpdate();
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
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
	}

}

//���̃|�W�V�����Z�b�g
void UserPlanetBase::SetNextPosition(const XMFLOAT3& nextPos)
{
	ARGUMENT_INITIALIZE(nextPos_, nextPos);           //���̈ʒu�ݒ�
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Move); //��Ԑݒ�
}

//�I������Ă��Ȃ��̂Ȃ痎����
void UserPlanetBase::Fall()
{
	//���Ƃ�
	transform_.position_.y -= FALL_SPEED;

	//�����폜����l��艺�Ȃ�폜
	if (transform_.position_.y < KILL_VALUE) KillMe();
}

//�I������Ă��邩�ǂ���
bool UserPlanetBase::IsSelect()
{
	//�����I������Ă���̂Ȃ�
	if (isSelect_)
	{
		//�I������
		ARGUMENT_INITIALIZE(isSelect_, false);
		return true;
	}

	return false;
}

//��Ԃ��Z�b�g
bool UserPlanetBase::SetStatus(PlanetStatus status)
{
	//�����I������Ă��Ȃ��̂Ȃ�
	if (!isSelect_)
	{
		ARGUMENT_INITIALIZE(status_, status);
		return true;
	}
	
	return false;
}

//�I������Ă��邩�ǂ����Z�b�g
void UserPlanetBase::SetIsSelect(const bool& flag)
{
	 ARGUMENT_INITIALIZE(isSelect_, flag);
}