#include "JumpRotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//�X�V
void JumpRotationningState::Update()
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

	HandleInput();
}

//���͂ɂ���ď�ԕω�����
void JumpRotationningState::HandleInput()
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void JumpRotationningState::Enter()
{
	//�W�����v�̃x�N�g���E��]�t���O������
	ARGUMENT_INITIALIZE(vJamp_, (GameManager::GetpPlayer()->GetNormal()) / 2);
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);
}