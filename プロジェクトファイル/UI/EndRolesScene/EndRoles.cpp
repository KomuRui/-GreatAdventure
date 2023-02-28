#include "EndRoles.h"
#include "../../Engine/ResourceManager/Image.h"

//�萔
namespace
{
	static const float MOVE_RANGE = 13.6f;      //�ړ��ł���͈�
	static const float START_Y_POS = -13.0f;	//����
	static const float MOVE_ADD_VALUE = 0.015f; //�ړ�����Ƃ��̉��Z��
}

//�R���X�g���N�^
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name),hReturnImage_(ZERO)
{
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void EndRoles::ChildStartUpdate()
{
	//�摜���[�h
	hReturnImage_ = Image::Load("Image/EndRole/ReturnTitle.png");
	assert(hReturnImage_ >= ZERO);

	//�g�����X�t�H�[���ݒ�
	tReturnImage_.position_.x = 0.6f;
	tReturnImage_.position_.y = -0.7f;

	//�����ʒu
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//�X�V
void EndRoles::ChildUpdate()
{
	//�ړ��͈͓��Ȃ�ړ�
	if(transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;
}

//�`��
void EndRoles::ChildDraw()
{
	//�ړ��͈͊O�Ȃ�`��
	if (transform_.position_.y >= MOVE_RANGE)
	{
		Image::SetTransform(hReturnImage_, tReturnImage_);
		Image::Draw(hReturnImage_);
	}
}