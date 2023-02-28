#include "EndRoles.h"
#include "../../Engine/ResourceManager/Image.h"

//�萔
namespace
{
	static const float RETURN_IMAGE_X_POS = 0.6f;  //����X�ʒu
	static const float RETURN_IMAGE_Y_POS = -0.7f; //����Y�ʒu
	static const float MOVE_RANGE = 13.6f;         //�ړ��ł���͈�
	static const float START_Y_POS = -13.0f;	   //����
	static const float MOVE_ADD_VALUE = 0.015f;    //�ړ�����Ƃ��̉��Z��
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
	ARGUMENT_INITIALIZE(tReturnImage_.position_.x,RETURN_IMAGE_X_POS);
	ARGUMENT_INITIALIZE(tReturnImage_.position_.y,RETURN_IMAGE_Y_POS);

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