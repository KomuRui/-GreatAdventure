#include "NewFileOKButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

//�R���X�g���N�^
NewFileOKButton::NewFileOKButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{

	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hNotSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void NewFileOKButton::IsButtonPush()
{

}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void NewFileOKButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void NewFileOKButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }