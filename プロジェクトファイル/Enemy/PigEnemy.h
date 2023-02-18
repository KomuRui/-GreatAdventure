#pragma once
#include "Enemy.h"

/// <summary>
/// �؂̓G�N���X
/// </summary>
class PigEnemy : public Enemy
{
protected:


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
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);
	
	//�R���X�g���N�^
	PigEnemy(GameObject* parent, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////
	
	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	//�m�b�N�o�b�N���Ď��S
	virtual void KnockBackDie() override;

	//���S
	virtual void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	virtual void OnCollision(GameObject* pTarget) override;

	//////////////////////////////�֐�///////////////////////////////

	/// <summary>
	/// �p����p�̍X�V�̑O�Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void ChildPigEnemyStartUpdate() {};

	/// <summary>
	/// �p����p�̍X�V
	/// </summary>
	virtual void ChildPigEnemyUpdate() {};

	/// <summary>
	/// Player�����g�̏�ɂ��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ炢��,false�Ȃ炢�Ȃ�</returns>
	bool IsPlayerTop();

	
};