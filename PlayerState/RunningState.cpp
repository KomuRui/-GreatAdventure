#include "RunningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//�X�V
void RunningState::Update2D()
{
	HandleInput();
}

//3D�p�X�V
void RunningState::Update3D()
{
	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void RunningState::HandleInput()
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerState::state_ = PlayerState::jumping_;
		PlayerState::state_->Enter();
	}

	//��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		PlayerState::state_ = PlayerState::rotationning_;
		PlayerState::state_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RunningState::Enter()
{
}