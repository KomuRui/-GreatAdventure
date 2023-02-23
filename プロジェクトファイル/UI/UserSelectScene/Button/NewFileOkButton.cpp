#include "NewFileOkButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../NewFileUI.h"

//�R���X�g���N�^
NewFileOkButton::NewFileOkButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void NewFileOkButton::ChildInitialize()
{
	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Ok_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void NewFileOkButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((NewFileUI*)GetParent())->ChangeEasingMove();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void NewFileOkButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void NewFileOkButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }