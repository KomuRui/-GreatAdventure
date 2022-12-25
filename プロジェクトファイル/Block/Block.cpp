#include "Block.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isHit_(false), hitMovePos_(0, 0, 0), initialPos_(0, 0, 0)
{
}

//������
void Block::ChildInitialize()
{
	//�p����p
	BlockChildInitialize();
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void Block::ChildStartUpdate()
{
	//�����������̃|�W�V�����ݒ�(���a�����)
	hitMovePos_ = VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal_) * 0.5));

	//�����l�̃|�W�V�����ݒ�
	initialPos_ = transform_.position_;

	//���C�̓����蔻��ɂȂ�悤�ɐݒ�
	Model::SetRayFlag(hModel_, true);

	//�p����p
	BlockChildStartUpdate();
}

//�X�V
void Block::ChildUpdate()
{
	//�������Ă���Ȃ�֐��Ăяo��
	if (isHit_) HitToLowerPlayer();

	//�p����p
	BlockChildUpdate();
}

//�`��
void Block::ChildDraw()
{
	//�p����p
	BlockChildDraw();
}

//Player�������瓖���������̋���
void Block::HitToLowerPlayer()
{
	//��Ԃ��Ȃ���ړI�̃|�W�V�����܂ŕύX���Ă���
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), 0.20));

	//������0.1��菬�����Ȃ玟�̖ړI�n��ݒ�
	if (RangeCalculation(transform_.position_, hitMovePos_) < 0.1)
	{
		//�������I����Ă���Ȃ�
		if (count_ == 1)
		{
			//�ۑ����Ă���
			XMFLOAT3 KeepPos = initialPos_;

			//���ׂď�����Ԃɂ��Ă���
			transform_.position_ = hitMovePos_;
			isHit_ = false;
			initialPos_ = hitMovePos_;
			hitMovePos_ = KeepPos;
			count_ = 0;
		}
		else
		{
			//�ۑ����Ă���
			XMFLOAT3 KeepPos = hitMovePos_;

			//�ړI�n�ύX
			transform_.position_ = hitMovePos_;
			hitMovePos_ = initialPos_;
			initialPos_ = KeepPos;
			count_++;
		}
	}
}

