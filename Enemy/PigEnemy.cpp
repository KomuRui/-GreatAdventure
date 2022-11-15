#include "PigEnemy.h"
#include "../Engine/Model.h"

//コンストラクタ
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name)
{
}

//更新の前に一回呼ばれる関数
void PigEnemy::EnemyChildStartUpdate()
{
	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, 1, 60, 3);
}