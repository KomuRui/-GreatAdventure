#include "BossEnemyMovie.h"

//コンストラクタ
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie")
{}

//初期化
void BossEnemyMovie::ChildInitialize()
{
	/////////////////明るさ設定/////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//更新の前に一回呼ばれる関数
void BossEnemyMovie::ChildStartUpdate()
{}

//更新
void BossEnemyMovie::ChildUpdate()
{
	

}