#include "JumpingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Global.h"
#include "PlayerState.h"

//�X�V
void JumpingState::Update()
{
	//�W�����v����x�N�g�����v���X��������
	if (XMVectorGetY(vJamp_) >= 0)
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60);
	}

	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void JumpingState::HandleInput()
{
	//�W�����v��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		GameManager::GetpPlayer()->pState_ = PlayerState::jumpRotationning_;
		GameManager::GetpPlayer()->pState_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpingState::Enter()
{
	//�W�����v�̃x�N�g���E�t���O������
	ARGUMENT_INITIALIZE(vJamp_, (XMVectorSet(0, 1, 0, 0)) / 2);
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//��ɌĂ�ł���
	Update();
}