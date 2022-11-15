#include "DropEnemy.h"
#include "../Engine/Model.h"

//コンストラクタ
DropEnemy::DropEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name)
{
}

//更新の前に一回呼ばれる関数
void DropEnemy::EnemyChildStartUpdate()
{
	///////////////モデルデータのロード///////////////////

	hHedModel_ = Model::Load("Enemy/Model/DropEnemyHed.fbx");
	assert(hHedModel_ >= 0);

	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, 1, 60, 3);
}

//更新
void DropEnemy::EnemyChildUpdate()
{
	Model::SetSpeculer(hHedModel_, XMFLOAT4(((rand() % 11)  / 10) + 0.2, ((rand() % 11) / 10) + 0.2, ((rand() % 11) / 10) + 0.2, 1.0f));
}

//描画
void DropEnemy::EnemyChildDraw()
{
	Model::SetTransform(hHedModel_, transform_);
	Model::Draw(hHedModel_);
}
