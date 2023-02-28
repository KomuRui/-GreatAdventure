#include "EndRoles.h"

//�萔
namespace
{
	static const float MOVE_RANGE = 13.4f;      //�ړ��ł���͈�
	static const float START_Y_POS = -13.0f;	//����
	static const float MOVE_ADD_VALUE = 0.008f; //�ړ�����Ƃ��̉��Z��
}

//�R���X�g���N�^
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void EndRoles::ChildStartUpdate()
{
	//�����ʒu
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//�X�V
void EndRoles::ChildUpdate()
{
	//�ړ��͈͓��Ȃ�ړ�
	if(transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;
}