#include "NewFileCancelButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"
#include "../../Engine/Time.h"
#include "../../Engine/Easing.h"
#include "../UserSelectNewFileUI.h"

//�R���X�g���N�^
NewFileCancelButton::NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath,name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void NewFileCancelButton::ChildInitialize()
{
	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void NewFileCancelButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((UserSelectNewFileUI*)GetParent())->SetPush(true);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void NewFileCancelButton::IsButtonSelect(){ ARGUMENT_INITIALIZE(hPict_, hSelectPict_);}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void NewFileCancelButton::IsButtonSelectRelease(){ ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_);}