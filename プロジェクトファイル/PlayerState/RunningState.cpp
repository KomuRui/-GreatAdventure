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
		PlayerState::playerState_ = PlayerState::playerJumping_;
		PlayerState::playerState_->Enter();
	}

	//��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		PlayerState::playerState_ = PlayerState::playerRotationning_;
		PlayerState::playerState_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RunningState::Enter()
{
}