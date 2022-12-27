#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//XV
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//“ü—Íˆ—
	HandleInput(enemy);
}

//3D—pXV
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//‰ñ“]
	enemy->Rotation();

	//“ü—Íˆ—
	HandleInput(enemy);
}

//“ü—Í‚É‚æ‚Á‚Äó‘Ô•Ï‰»‚·‚é
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//ó‘Ô•Ï‰»‚µ‚½‚Æ‚«ˆê‰ñ‚¾‚¯ŒÄ‚Î‚ê‚éŠÖ”
void EnemyRotationState::Enter(Enemy* enemy)
{
    //‰ñ“]‚·‚é•ûŒüÝ’è
    enemy->SetRotationSign(rand() % 2 == 1 ? 1 : -1);

    //‰ñ“]Šp“xÝ’è
    enemy->SetRotationAngle(XMConvertToRadians((rand() % 141) + 40));

    //‚Ç‚Ì‚­‚ç‚¢‰ñ“]‚µ‚½‚©‚ð‰Šú‰»
    enemy->SetRotationTotal(ZERO);
}