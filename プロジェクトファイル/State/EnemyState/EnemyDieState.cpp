#include "EnemyDieState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//�X�V
void EnemyDieState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyDieState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyDieState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyDieState::Enter(Enemy* enemy)
{
}