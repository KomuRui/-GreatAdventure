#pragma once
#include "../State.h"

/// <summary>
/// �ړ���Ԃ̃N���X
/// </summary>
class PigEnemyMoveState : public State
{
	int operationTime_;     //���̏�Ԃɕς��܂ł̎���
	int stateCount_;        //���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������

public:

	//2D�p�X�V
	void Update2D() override;

	//3D�p�X�V
	void Update3D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;
};