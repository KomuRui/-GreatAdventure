#include "PigEnemyKnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//�X�V
void PigEnemyKnockBackState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void PigEnemyKnockBackState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void PigEnemyKnockBackState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyKnockBackState::Enter(Enemy* enemy)
{
}