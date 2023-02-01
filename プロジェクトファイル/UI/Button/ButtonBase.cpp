#include "ButtonBase.h"

//�R���X�g���N�^
ButtonBase::ButtonBase(GameObject* parent, std::string modelPath, std::string name)
	:ImageBase(parent,modelPath,name), isSelect_(false)
{}


//�X�V
void ButtonBase::ChildUpdate()
{
	//�����I������Ă���̂Ȃ�
	if (isSelect_)
	{
		//�ݒ肳��Ă���֐����Ăяo��
		IsButtonSelecting(ButtonSelectingFunc);
	}

	//�����I������Ă��邩��A�{�^�����������̂Ȃ�
	if (isSelect_ && Input::IsPadButtonDown(Input::IsPadButton(XINPUT_GAMEPAD_A)))
	{
		//�ݒ肳��Ă���֐����Ăяo��
		IsButtonPush(OnPushFunc);
	}
}

//�I������Ă��邩���Z�b�g 
void ButtonBase::SetSelect(bool flag)
{
	//�����I������Ă��Ȃ����ݒ肳���flag��true�Ȃ�
	if (!isSelect_ && flag) IsButtonPush(ButtonSelectFunc);

	//�����I������Ă��Đݒ肳���flag��false�Ȃ�
	if (isSelect_ && !flag) IsButtonSelectRelease(ButtonSelectReleaseFunc);

	//�ݒ�
	ARGUMENT_INITIALIZE(isSelect_, flag);
}