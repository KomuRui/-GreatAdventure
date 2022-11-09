#pragma once
#include "../Mob.h"

//���[�v�N���X
class Warp : public Mob
{
private:

	//�萔
	const float    ROTATION_QUANTITY = 0.02f;        //��]��
	const float    ADDITION_TURNOVERRATE = 0.02f;   //��]�������Z�����
	const float    MAX_TURNOVERRATE = 5.0f;         //�ő��]��
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };     //�R���C�_�[�|�W�V����
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 }; //�R���C�_�[�T�C�Y

	//�ϐ�
	float    turnoverRate_;  //��]��
	int      status_;        //���
	XMFLOAT3 playerPos_;     //���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�

	//���[�v�ɏ��
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

public:

	//�R���X�g���N�^
	Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(Stop)
		, turnoverRate_(1), playerPos_(0, 0, 0)
	{}

	//������
	void ChildInitialize() override
	{
		//���g�ɓ����蔻���ǉ�
		BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
		AddCollider(collision);

		//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
		playerPos_ = { transform_.position_.x,transform_.position_.y - 1.0f,transform_.position_.z };
	}

	//���[�v�̓�����
	void UpdateMove() override
	{
		//Y����]������
		Angle += ROTATION_QUANTITY * turnoverRate_;

		//Y���̊p�x��360���傫���Ȃ�0�ɖ߂�
		if (Angle > TWOPI_DEGREES) Angle = ZEROPI_DEGREES;
	}

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		//Player�ƏՓ˂�����
		if (pTarget->GetObjectName() == "Player")
		{
			//Player�|�W�V�������Z�b�g����
			pTarget->SetPosition(playerPos_);

			//Player�Ɠ������Ă����ԂȂ��]�����ǂ�ǂ񑁂߂�
			//������]�����ő�܂ŒB�������Ԃ�Move�ɐݒ�
			(turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = Move);
		}
	}

};

