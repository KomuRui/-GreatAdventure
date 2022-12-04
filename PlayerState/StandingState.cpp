#include "StandingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//�X�V
void StandingState::Update()
{
	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput()
{
	//�W�����v��ԂɕύX
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		GameManager::GetpPlayer()->pState_ = PlayerState::jumping_;
		GameManager::GetpPlayer()->pState_->Enter();
	}

	//�����ԂɕύX
	if (Input::GetPadTrrigerL())
	{
		//��ԕύX
		GameManager::GetpPlayer()->pState_ = PlayerState::running_;
		GameManager::GetpPlayer()->pState_->Enter();
	}

	//��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		GameManager::GetpPlayer()->pState_ = PlayerState::rotationning_;
		GameManager::GetpPlayer()->pState_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter()
{
}
