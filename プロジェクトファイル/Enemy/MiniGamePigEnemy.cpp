#include "MiniGamePigEnemy.h"
#include "../Manager/GameManager/GameManager.h"

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void MiniGamePigEnemy::ChildPigEnemyStartUpdate()
{
	///////////////���邳///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void MiniGamePigEnemy::ChildPigEnemyUpdate()
{
	//Player�����ɍs�����玀�S
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();
}
