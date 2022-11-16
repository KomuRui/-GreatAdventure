#pragma once
#include "Enemy.h"

class PigEnemy : public Enemy
{
	//�m�b�N�o�b�N�̕����Ƌ���
	XMVECTOR knockBackDir_;

	//�m�b�N�o�b�N�������ǂ���
	bool knockBackFlag_;

public:

	//�R���X�g���N�^
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	//�m�b�N�o�b�N���Ď��S
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;
};