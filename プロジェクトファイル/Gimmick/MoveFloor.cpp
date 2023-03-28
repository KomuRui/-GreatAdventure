#include "MoveFloor.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"

//�萔
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.03f; //��ԌW��
	static const float TARGET_CHANGE_DISTANCE = 0.5f;     //�ړI�n��ύX����Ƃ��̋���
}

//�R���X�g���N�^
MoveFloor::MoveFloor(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
{
}

MoveFloor::~MoveFloor()
{
}

//�X�^�[�g�A�b�v�f�[�g
void MoveFloor::ChildStartUpdate()
{
	//Player�ɓ����蔻�肳���邽�߂ɒǉ�
	Model::SetRayFlag(hModel_, true);

	//���̖ړI�n�ݒ�
	MoveFloorTarget_ = { 31.0f, 20.14928f, -15.2083f };
}

//�X�V
void MoveFloor::ChildUpdate()
{
	//��Ԃ�Move�Ȃ�
	if (status_ == MOVE) MovingToPurpose();
}

//���̖ړI�n�܂ňړ�
void MoveFloor::MovingToPurpose()
{
	//���̃^�[�Q�b�g�ۑ����Ă������߂̕ϐ�
	static XMFLOAT3 target = transform_.position_;

	//�⊮���Ȃ���ړ�
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&MoveFloorTarget_), INTERPOLATION_COEFFICIENT));

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = RangeCalculation(transform_.position_, MoveFloorTarget_);

	//������0.5��菬�����Ȃ�^�[�Q�b�g�ς���
	if (dist < TARGET_CHANGE_DISTANCE)
	{
		transform_.position_ = MoveFloorTarget_;
		MoveFloorTarget_ = target;
		target = transform_.position_;
	}

}