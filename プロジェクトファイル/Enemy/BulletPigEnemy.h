#pragma once
#include "Enemy.h"

/// <summary>
/// ���ł؃N���X
/// </summary>
class BulletPigEnemy : public Enemy
{

public:

	//�R���X�g���N�^
	BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void EnemyChildStartUpdate() override;

	//����
	void Move() override;

	/// <summary>
	/// ������
	/// </summary>
	void ShotBullet();

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;
};

