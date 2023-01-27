#include "StandingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"

//�X�V
void StandingState::Update2D(PlayerBase* player)
{
	//���C�����ɔ�΂�
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(DOWN_VECTOR));
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//���C�̓�������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		player->SetPosition(dataNormal.pos);
		player->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//3D�p�X�V
void StandingState::Update3D(PlayerBase* player)
{
	//���C�����ɔ�΂�
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(player->GetDown()));
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < 0.9f)
	{
		//�n�`�ɍ������킹��
		player->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + player->GetNormal()));
		player->SetAcceleration(1);
	}

	//���͏����֐����Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void StandingState::HandleInput(PlayerBase* player)
{
	//�W�����v��ԂɕύX
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}

	//��]��ԂɕύX
	if (Input::GetPadTrrigerR())
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void StandingState::Enter(PlayerBase* player)
{
}
