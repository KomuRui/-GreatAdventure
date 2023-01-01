#pragma once
#include "Enemy.h"

/// <summary>
/// 球打つ豚クラス
/// </summary>
class BulletPigEnemy : public Enemy
{

public:

	//コンストラクタ
	BulletPigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一度だけ呼ばれる
	void EnemyChildStartUpdate() override;

	//動き
	void Move() override;

	/// <summary>
	/// 球発射
	/// </summary>
	void ShotBullet();

	//当たり判定
	void OnCollision(GameObject* pTarget) override;
};

