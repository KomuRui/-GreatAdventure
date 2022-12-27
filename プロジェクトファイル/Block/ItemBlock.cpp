#include "ItemBlock.h"

//�萔
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.05f; //��]����Ƃ��ɉ��Z����p�x
}

//�R���X�g���N�^
ItemBlock::ItemBlock(GameObject* parent, std::string modelPath, std::string name)
	: Block(parent, modelPath, name), type_(ItemBlockNormal)
{
}

//�X�V
void ItemBlock::BlockChildUpdate()
{
	//�����^��Rotation�Ȃ�
	if (type_ == ItemBlockRotation) Move();
}

//�u���b�N�̓���
void ItemBlock::Move()
{
	angle_ += ADD_ROTATION_ANGLE;
}
