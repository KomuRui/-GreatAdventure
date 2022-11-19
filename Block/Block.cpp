#include "Block.h"

//�R���X�g���N�^
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name),isHit_(false), hitMovePos_(0,0,0)
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
	hitMovePos_ = Transform::VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal) * 0.5));

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
	transform_.position_ = Transform::VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), 0.5));
}

