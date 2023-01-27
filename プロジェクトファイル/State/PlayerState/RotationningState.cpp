#include "RotationningState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "PlayerStateManager.h"
#include "../../Engine/Model.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Player/PlayerBase.h"

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
void RotationningState::Update2D(PlayerBase* player)
{
	//���Ƀ��C���΂�
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(DOWN_VECTOR));
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//���C�̓�������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE_2D)
	{
		dataNormal.pos.y += HIT_DISTANCE_2D;
		player->SetPosition(dataNormal.pos);
		player->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Player�̏㎲������]������
	player->SetAngle(player->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
	    //��]��~
		ARGUMENT_INITIALIZE(rotationCount_,ZERO);

		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput(player);
}

//3D�p�X�V
void RotationningState::Update3D(PlayerBase* player)
{
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(player->GetDown()));
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE)
	{
		//�n�`�ɍ������킹��
		player->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + player->GetNormal()));
		player->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Player�̏㎲������]������
	player->SetAngle(player->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
		//��]��~
		ARGUMENT_INITIALIZE(rotationCount_, ZERO);

		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void RotationningState::HandleInput(PlayerBase* player)
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RotationningState::Enter(PlayerBase* player)
{
	//0�ɏ�����
	ZERO_INITIALIZE(rotationCount_);
}