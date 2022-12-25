#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../State.h"
#include "PigEnemyDieState.h"
#include "PigEnemyKnockBackState.h"
#include "PigEnemyMoveState.h"
#include "PigEnemyRotationState.h"
#include "PigEnemyWaitState.h"

//Player�̏�Ԃ̊��N���X
class PigEnemyState : public State
{
public:

	//��Ԃ������ϐ�
	static State* pigEnemyState_;

	//�e��ԕϐ�
	static PigEnemyDieState* pigEnemyDie_;             //���S
	static PigEnemyKnockBackState* pigEnemyKnockBack_; //�m�b�N�o�b�N
	static PigEnemyMoveState* pigEnemyMove_;		   //�ړ�
	static PigEnemyRotationState* pigEnemyRotation_;   //��]
	static PigEnemyWaitState* pigEnemyWait_;		   //�ҋ@

	//�R���X�g���N�^
	PigEnemyState();

	//2D�p�X�V
	void Update2D() override;

	//3D�p�X�V
	void Update3D() override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput() override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter() override;

};



