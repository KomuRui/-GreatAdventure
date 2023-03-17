#include "PauseOperationButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//�R���X�g���N�^
PauseOperationButton::PauseOperationButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1),hSelectPict2_(-1)
{}

//������
void PauseOperationButton::ChildInitialize()
{
	////////////////////////////////�摜�̏����ݒ�////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/Operation_Select.png"));
	ARGUMENT_INITIALIZE(hSelectPict2_, Image::Load("Image/Pause/Operation_Explain.png"));
}

//�`��
void PauseOperationButton::ChildDraw()
{
	//�I������Ă���̂Ȃ�
	if (isSelect_)
	{
		Transform t;
		Image::SetTransform(hSelectPict2_, t);
		Image::Draw(hSelectPict2_);
	}
}


//�{�^���������ꂽ�牽���邩
void PauseOperationButton::IsButtonPush()
{
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void PauseOperationButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void PauseOperationButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
