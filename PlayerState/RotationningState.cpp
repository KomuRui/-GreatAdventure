#include "RotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"
#include "../Engine/Model.h"

//�X�V
void RotationningState::Update2D()
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

	//�G�t�F�N�g�̕\��
	GameManager::GetpPlayer()->RotationEffect();

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (1 - (rotationCount_ * 0.015f)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= 60)
	{
	    //��]��~
	    rotationCount_ = 0;

		//��ԕύX
		PlayerState::state_ = PlayerState::standing_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void RotationningState::HandleInput()
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerState::state_ = PlayerState::jumping_;
		PlayerState::state_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RotationningState::Enter()
{
	//0�ɏ�����
	ZERO_INITIALIZE(rotationCount_);
}