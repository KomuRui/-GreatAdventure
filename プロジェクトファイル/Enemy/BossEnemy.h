#pragma once
#include "Enemy.h"
#include "../Engine/Component/Gauge.h"
#include "../UI/TalkImage.h"
#include "../UI/WorldScene/World2/BossWarningImage.h"

/// <summary>
/// �Ō�̃{�X
/// </summary>
class BossEnemy : public Enemy
{
	//�{�X�̗̑�
	int hp_;

	//�^�C�}�[�ԍ�
	int hTime_;

	//�b���摜
	TalkImage* pTalkImage_;

	//�x���摜
	BossWarningImage* pWarningImage_;

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


	//////////////////////////////�I�[�o�[���C�h����֐�///////////////////////////////////

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�ړ�
	void Move() override;

	//��]
	void Rotation() override;

	//�X�V
	void EnemyChildUpdate() override;

	//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	void PlayerNearWithIsCheck() override {};

	//�m�b�N�o�b�N
	void KnockBackDie() override;

	//���S
	void Die() override;

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����̃I�u�W�F�N�g�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;

	////////////////////////////////�֐�///////////////////////////////////

	/// <summary>
	/// ����
	/// </summary>
	void Generation();

	/// <summary>
	/// �b���摜��`�悷��悤��
	/// </summary>
	void SetTalkImageDraw();
};

