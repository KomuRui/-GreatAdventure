#pragma once
#include "../Mob.h"

class BulletPigEnemy : public Mob
{
	//定数

	const int ANIM_START_FREAM = 0;
	const int ANIM_END_FREAM = 30;
	const float ANIM_SPEED = 1.0f;


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

