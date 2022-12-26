#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../EnemyState.h"
#include "PigEnemyStateManager.h"
#include "PigEnemyDieState.h"
#include "PigEnemyKnockBackState.h"
#include "PigEnemyMoveState.h"
#include "PigEnemyRotationState.h"
#include "PigEnemyWaitState.h"

//�O��`
class Enemy;

/// <summary>
/// PigEnemy�̏�Ԃ��Ǘ�
/// </summary>
class PigEnemyStateManager : public EnemyState
{

public:

	//��Ԃ������ϐ�
	static EnemyState* pigEnemyState_;

	//�e��ԕϐ�
	static PigEnemyDieState* pigEnemyDie_;             //���S
	static PigEnemyKnockBackState* pigEnemyKnockBack_; //�m�b�N�o�b�N
	static PigEnemyMoveState* pigEnemyMove_;		   //�ړ�
	static PigEnemyRotationState* pigEnemyRotation_;   //��]
	static PigEnemyWaitState* pigEnemyWait_;		   //�ҋ@

	//�R���X�g���N�^
	PigEnemyStateManager();

	//2D�p�X�V
	void Update2D(Enemy* enemy) override;

	//3D�p�X�V
	void Update3D(Enemy* enemy) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(Enemy* enemy) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(Enemy* enemy) override;

};



