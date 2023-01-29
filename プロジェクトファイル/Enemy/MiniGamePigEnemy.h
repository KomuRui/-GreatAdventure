#pragma once
#include "PigEnemy.h"

/// <summary>
/// �~�j�Q�[���p�̓؂̓G
/// </summary>
class MiniGamePigEnemy : public PigEnemy
{

public:

	//�R���X�g���N�^
	MiniGamePigEnemy(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildPigEnemyStartUpdate() override;

	//�X�V
	void ChildPigEnemyUpdate() override;

	//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	void PlayerNearWithIsCheck() override {};

	//�m�b�N�o�b�N���Ď��S
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;

};

