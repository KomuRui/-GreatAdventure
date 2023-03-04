#pragma once
#include "Enemy.h"

/// <summary>
/// �Ō�̃{�X
/// </summary>
class BossEnemy : public Enemy
{
	//�{�X�̗̑�
	int hp_;

	///////////////�m�b�N�o�b�N///////////////////

	//�m�b�N�o�b�N�̕����Ƌ���
	XMVECTOR knockBackDir_;

	//���ԂƂ��̌��ƂȂ��x�N�g��
	XMVECTOR vFly_;

	//���ƂȂ�t���C�x�N�g����ۑ����Ă���
	XMVECTOR keepFly_;

	//�m�b�N�o�b�N�������ǂ���
	bool isKnockBack_;


public:

	//�R���X�g���N�^
	BossEnemy(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	//Player�����p���A�w�苗�����ɂ��鎞�̏���
	void PlayerWithIf() override;

	//Player�����p���A�w�苗�����ɂ��Ȃ����̏���
	void NotPlayerWithIf() override;

	//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	void PlayerNearWithIsCheck() override {};

	//��ɒT���͈͓��ɂ���悤��
	bool IsInSearchRange() override { return true; }

	//�m�b�N�o�b�N
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;
};

