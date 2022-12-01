#include "MoveFloor.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
MoveFloor::MoveFloor(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(MOVE)
,number_(0)
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

	MoveFloorTarget_ = { 31, 20.14928, -15.2083 };
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
	static XMFLOAT3 a = transform_.position_;

	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&MoveFloorTarget_), 0.03));

	//���̃|�W�V�����ƖړI�n�̋��������߂�
	float dist = Transform::RangeCalculation(transform_.position_, MoveFloorTarget_);


	//������1��菬�����Ȃ�^�[�Q�b�g�ς���
	if (dist < 0.5)
	{
		transform_.position_ = MoveFloorTarget_;
		MoveFloorTarget_ = a;
		a = transform_.position_;
	}

}