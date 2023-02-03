#include "MainCharIconButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../NewFileUI.h"

//�R���X�g���N�^
MainCharIconButton::MainCharIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void MainCharIconButton::ChildInitialize()
{
	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/MainCharIcon_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void MainCharIconButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((NewFileUI*)GetParent())->ChangeEasingMove();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void MainCharIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void MainCharIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }