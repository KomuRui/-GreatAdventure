#include "StandingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Model.h"
#include "PlayerState.h"

//�X�V
void StandingState::Update2D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	XMFLOAT3 moveY2 = { 0,-1,0 };
	dataNormal.dir = moveY2;
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput();
}

//3D�p�X�V
void StandingState::Update3D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::BlockRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < 0.9f)
	{
		//�n�`�ɍ������킹��
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput()
{
	//�W�����v��ԂɕύX
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
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
void StandingState::Enter()
{
}
