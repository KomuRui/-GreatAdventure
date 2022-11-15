#pragma once
#include "Enemy.h"

class PigEnemy : public Enemy
{

public:

	//コンストラクタ
	PigEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;
};