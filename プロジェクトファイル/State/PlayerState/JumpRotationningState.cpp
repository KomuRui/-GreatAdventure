#include "JumpRotationningState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "PlayerStateManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"

//�萔
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //�W�����v�x�N�g���̑傫��
	const float ADD_ROTATION_ANGLE = 0.5f; //��]����Ƃ����Z����p�x
	const float JUMP_VECTOR_DOWN = 0.015f; //�W�����v�x�N�g�������������Ă����Ƃ��̒l
}

//�X�V
void JumpRotationningState::Update2D(PlayerBase* player)
{
	//�����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}
	
	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Player�̏㎲������]������
	player->SetAngle(player->GetAngle() + ADD_ROTATION_ANGLE);

	//���͏������Ă�
	HandleInput(player);
}

//3D�p�X�V
void JumpRotationningState::Update3D(PlayerBase* player)
{
	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		ARGUMENT_INITIALIZE(vJamp_,vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN));
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Player�̏㎲������]������
	player->SetAngle(player->GetAngle() + ADD_ROTATION_ANGLE);

	//���͏������Ă�
	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void JumpRotationningState::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpRotationningState::Enter(PlayerBase* player)
{
	//�W�����v�̃x�N�g���E�t���O������
	//3D��2D�ŏ������̒l�ς���
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, player->GetNormal() * JUMP_VECTOR_SIZE);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR * JUMP_VECTOR_SIZE);

	//��]��
	PlayerAudioManager::RotationAudio();

	//��ƂȂ�W�����v�x�N�g����ۑ����Ă���
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3D��2D�ŌĂԊ֐��ς���
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}