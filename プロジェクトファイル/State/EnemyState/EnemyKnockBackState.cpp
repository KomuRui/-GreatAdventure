#include "EnemyKnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//�X�V
void EnemyKnockBackState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyKnockBackState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyKnockBackState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyKnockBackState::Enter(Enemy* enemy)
{
}