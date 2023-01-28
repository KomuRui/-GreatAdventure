#include "MiniGamePigEnemy.h"
#include "../Manager/GameManager/GameManager.h"

//更新の前に一度だけ呼ばれる関数
void MiniGamePigEnemy::ChildPigEnemyStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void MiniGamePigEnemy::ChildPigEnemyUpdate()
{
	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}
