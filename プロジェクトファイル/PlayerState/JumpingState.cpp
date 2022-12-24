#include "JumpingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Global.h"
#include "PlayerState.h"

//�X�V
void JumpingState::Update2D()
{
	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR / 60))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (UP_VECTOR / 60);
	}

	HandleInput();
}

//3D�p�X�V
void JumpingState::Update3D()
{
	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//�x�N�g���̒������ׂ�
		float len = sqrtf(XMVectorGetX(vJamp_) * XMVectorGetX(vJamp_) + XMVectorGetY(vJamp_) * XMVectorGetY(vJamp_) + XMVectorGetZ(vJamp_) * XMVectorGetZ(vJamp_));

		//�W�����v�x�N�g�����L�����̏㎲�ɒ���
		vJamp_ = GameManager::GetpPlayer()->GetNormal() * len;

		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60);
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
		PlayerState::state_ = PlayerState::jumpRotationning_;
		PlayerState::state_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpingState::Enter()
{
	//�W�����v�̃x�N�g���E�t���O������
	//3D��2D�ŏ������̒l�ς���
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() / 2);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR / 2);
	
	//��ƂȂ�W�����v�x�N�g����ۑ����Ă���
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3D��2D�ŌĂԊ֐��ς���
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D();
	else
		Update2D();
}