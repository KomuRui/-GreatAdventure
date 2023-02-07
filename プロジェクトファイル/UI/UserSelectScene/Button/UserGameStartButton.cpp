#include "UserGameStartButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../../../Engine/Time.h"
#include "../../../Engine/Easing.h"
#include "../NewFileUI.h"

//�R���X�g���N�^
UserGameStartButton::UserGameStartButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void UserGameStartButton::ChildInitialize()
{
	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void UserGameStartButton::IsButtonPush()
{
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }