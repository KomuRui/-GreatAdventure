#pragma once
#include "Enemy.h"

class DropEnemy : public Enemy
{
	//頭のモデル
	int hHedModel_; 

public:

	//コンストラクタ
	DropEnemy(GameObject* parent, std::string modelPath, std::string name);

	//更新の前に一回呼ばれる関数
	void EnemyChildStartUpdate() override;

	//更新
	void EnemyChildUpdate() override;

	//描画
	void EnemyChildDraw() override;
};

