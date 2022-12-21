#pragma once
#include "../Mob.h"

class BulletPigEnemy : public Mob
{
	//定数

	const int PIG_ENEMY_ANIM_START_FREAM = 0;
	const int PIG_ENEMY_ANIM_END_FREAM = 90;
	const float PIG_ENEMY_ANIM_SPEED = 1.0f;


public:

	//コンストラクタ
	BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//球発射
	void ShotBullet();

	//当たり判定
	void OnCollision(GameObject* pTarget) override;
};

