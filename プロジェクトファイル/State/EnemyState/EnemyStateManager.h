#pragma once
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "EnemyState.h"
#include "EnemyStateManager.h"
#include "EnemyDieState.h"
#include "EnemyKnockBackState.h"
#include "EnemyMoveState.h"
#include "EnemyRotationState.h"
#include "EnemyWaitState.h"

//�O��`
class Enemy;

/// <summary>
/// PigEnemy�̏�Ԃ��Ǘ�
/// </summary>
class EnemyStateManager : public EnemyState
{

public:

	//�e��ԕϐ�
	static EnemyDieState* EnemyDie_;             //���S
	static EnemyKnockBackState* EnemyKnockBack_; //�m�b�N�o�b�N
	static EnemyMoveState* EnemyMove_;		    //�ړ�
	static EnemyRotationState* EnemyRotation_;   //��]
	static EnemyWaitState* EnemyWait_;		    //�ҋ@

	//�R���X�g���N�^
	EnemyStateManager();

	//2D�p�X�V
	void Update2D(Enemy* enemy) override;

	//3D�p�X�V
	void Update3D(Enemy* enemy) override;

	//���͂ɂ���ď�ԕω�����
	void HandleInput(Enemy* enemy) override;

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	void Enter(Enemy* enemy) override;

};



