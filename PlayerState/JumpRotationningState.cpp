#include "JumpRotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//�X�V
void JumpRotationningState::Update2D()
{
	//�����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (XMVectorSet(0,1,0,0) / 60))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60);
	}

	//�G�t�F�N�g�̕\��
	GameManager::GetpPlayer()->RotationEffect();

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + 0.5);

	//���͏������Ă�
	HandleInput();
}

//3D�p�X�V
void JumpRotationningState::Update3D()
{
	//��ƂȂ�W�����v�x�N�g���ƕ����������Ȃ�
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Player�W�����v�ړ�
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60))));

		//�ǂ�ǂ�W�����v�x�N�g�������������Ă���
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60);
	}

	//�G�t�F�N�g�̕\��
	GameManager::GetpPlayer()->RotationEffect();

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + 0.5);

	//���͏������Ă�
	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void JumpRotationningState::HandleInput()
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpRotationningState::Enter()
{
	//�W�����v�̃x�N�g���E�t���O������
	//3D��2D�ŏ������̒l�ς���
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() / 2);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, (XMVectorSet(0, 1, 0, 0)) / 2);

	//��ƂȂ�W�����v�x�N�g����ۑ����Ă���
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3D��2D�ŌĂԊ֐��ς���
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D();
	else
		Update2D();
}