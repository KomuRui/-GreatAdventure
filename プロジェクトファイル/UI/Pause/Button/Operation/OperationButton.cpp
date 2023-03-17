#include "OperationButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//�R���X�g���N�^
OperationButton::OperationButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//������
void OperationButton::ChildInitialize()
{
	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/Operation_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void OperationButton::IsButtonPush()
{
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void OperationButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void OperationButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
