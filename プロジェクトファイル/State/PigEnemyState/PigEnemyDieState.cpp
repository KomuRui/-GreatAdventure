#include "PigEnemyDieState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//�X�V
void PigEnemyDieState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void PigEnemyDieState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void PigEnemyDieState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyDieState::Enter(Enemy* enemy)
{
}