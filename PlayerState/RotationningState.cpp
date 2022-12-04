#include "RotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//�X�V
void RotationningState::Update()
{
	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void RotationningState::HandleInput()
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		GameManager::GetpPlayer()->pState_ = PlayerState::jumping_;
		GameManager::GetpPlayer()->pState_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RotationningState::Enter()
{
}