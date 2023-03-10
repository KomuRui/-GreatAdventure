#pragma once
#include "Enemy.h"

/// <summary>
/// �{�X�̎q���̃N���X
/// </summary>
class BossEnemyChild : public Enemy
{
private:

	///////////////�m�b�N�o�b�N///////////////////

	//�m�b�N�o�b�N�̕����Ƌ���
	XMVECTOR knockBackDir_;

	//���ԂƂ��̌��ƂȂ��x�N�g��
	XMVECTOR vFly_;

	//���ƂȂ�t���C�x�N�g����ۑ����Ă���
	XMVECTOR keepFly_;

	//�m�b�N�o�b�N�������ǂ���
	bool isKnockBack_;

	///////////////���̑�///////////////////

	//�R���C�_�[
	SphereCollider* collision;


public:

	//�R���X�g���N�^
	BossEnemyChild(GameObject* parent, std::string modelPath, std::string name);

	//�R���X�g���N�^
	BossEnemyChild(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

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

	//////////////////////////////�֐�///////////////////////////////

	/// <summary>
	/// �p����p�̍X�V�̑O�Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void ChildBossEnemyChildStartUpdate() {};

	/// <summary>
	/// �p����p�̍X�V
	/// </summary>
	virtual void ChildBossEnemyChildUpdate() {};

};