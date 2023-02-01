#include "NewFileCancelButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

//�R���X�g���N�^
NewFileCancelButton::NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath,name), hNotSelectPict_(-1)
{
	//���[�h
	ARGUMENT_INITIALIZE(hNotSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));

	
}


//�I���摜��ݒ�
void NewFileCancelButton::SetSelectImage()
{

}

//�I������Ă��Ȃ��Ƃ��̉摜��ݒ�
void NewFileCancelButton::SetNotSelectImage()
{

}

//�߂�
void NewFileCancelButton::Back()
{

}

//�A�C�R���I����
void NewFileCancelButton::GoIconSelect()
{

}