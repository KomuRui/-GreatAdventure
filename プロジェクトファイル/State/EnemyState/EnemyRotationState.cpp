#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//�X�V
void EnemyRotationState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyRotationState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyRotationState::Enter(Enemy* enemy)
{
}