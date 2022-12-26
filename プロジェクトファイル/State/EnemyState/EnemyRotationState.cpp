#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "../../Enemy/Enemy.h"

//’è”
namespace
{
    static const float ADD_ROTATION_ANGLE = 0.02f; //‰ñ“]‚·‚é‚Æ‚«‚Ì‰ÁZ‚·‚éŠp“x
}

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

    //ã²­‚µ‰ñ“]‚³‚¹‚ÄƒZƒbƒg
    enemy->SetAngle(enemy->GetAngle() + (ADD_ROTATION_ANGLE * rotationSign_));

    //‰ñ“]Šp“x‚æ‚è‰ñ“]‘”‚ª‘½‚­‚È‚Á‚½‚ç
    if (rotationTotal_ > rotationAngle_)
    {
        //0‚É‰Šú‰»
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //ó‘Ô‚ğ‘Ò‹@‚Éİ’è
        enemy->ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
    }

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
    rotationSign_ = rand() % 2 == 1 ? 1 : -1;
    rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
}