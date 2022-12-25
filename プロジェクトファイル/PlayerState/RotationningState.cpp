#include "RotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"
#include "../Engine/Model.h"

//�萔
namespace
{
	static const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");	//FPS
	static const int NORMAL_ROTATION_ANGLE = 1;       //��]����Ƃ��̉��Z����p�x
	static const float ROTATION_ATTENUATION = 0.015f; //��]�̌���
	static const float HIT_DISTANCE_2D = 1.0f; //���C�̓�����������(2D)
	static const float HIT_DISTANCE    = 0.9f; //���C�̓�����������(3D)
}

//�X�V
void RotationningState::Update2D()
{
	//���Ƀ��C���΂�
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(DOWN_VECTOR);
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//���C�̓�������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE_2D)
	{
		dataNormal.pos.y += HIT_DISTANCE_2D;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	GameManager::GetpPlayer()->RotationEffect();

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
	    //��]��~
		ARGUMENT_INITIALIZE(rotationCount_,ZERO);

		//��ԕύX
		PlayerState::playerState_ = PlayerState::playerStanding_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput();
}

//3D�p�X�V
void RotationningState::Update3D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE)
	{
		//�n�`�ɍ������킹��
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	GameManager::GetpPlayer()->RotationEffect();

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
		//��]��~
		ARGUMENT_INITIALIZE(rotationCount_, ZERO);

		//��ԕύX
		PlayerState::playerState_ = PlayerState::playerStanding_;
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
		PlayerState::playerState_ = PlayerState::playerJumping_;
		PlayerState::playerState_->Enter();
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RotationningState::Enter()
{
	//0�ɏ�����
	ZERO_INITIALIZE(rotationCount_);
}