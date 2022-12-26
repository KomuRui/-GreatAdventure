#include "EnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//�X�V
void EnemyMoveState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyMoveState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyMoveState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyMoveState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 19 + 12) * 10;
	ZERO_INITIALIZE(stateCount_);
}