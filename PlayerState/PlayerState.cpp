#include "PlayerState.h"

//�estatic�ϐ��̏�����
JumpingState* PlayerState::jumping_ = new JumpingState;
JumpRotationningState* PlayerState::jumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerState::rotationning_ = new RotationningState;
RunningState* PlayerState::running_ = new RunningState;
StandingState* PlayerState::standing_ = new StandingState;
WalkingState* PlayerState::walking_ = new WalkingState;


//�R���X�g���N�^
PlayerState::PlayerState()
{
	//�ŏ��̏�Ԃ͗����Ă�ɂ��Ă���
	ARGUMENT_INITIALIZE(state_, standing_);
}

//�X�V
void PlayerState::Update()
{
	//���݂̏�Ԃ̍X�V���Ă�
	state_->Update();
}

//���͂ɂ���ď�ԕω�����
void PlayerState::HandleInput()
{
	//���݂̏�Ԃ̓��͏������Ă�
	state_->HandleInput();
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PlayerState::Enter()
{
	//���݂̏�Ԃ�Enter�֐����Ă�
	state_->Enter();
}
