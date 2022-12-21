#pragma once
#include "../Mob.h"

class BulletPigEnemy : public Mob
{
	//�萔

	const int PIG_ENEMY_ANIM_START_FREAM = 0;
	const int PIG_ENEMY_ANIM_END_FREAM = 90;
	const float PIG_ENEMY_ANIM_SPEED = 1.0f;


public:

	//�R���X�g���N�^
	BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//������
	void ShotBullet();

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;
};

