#pragma once
#include "../Mob.h"

class BulletPigEnemy : public Mob
{
	//�萔

	const int ANIM_START_FREAM = 0;
	const int ANIM_END_FREAM = 30;
	const float ANIM_SPEED = 1.0f;


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

