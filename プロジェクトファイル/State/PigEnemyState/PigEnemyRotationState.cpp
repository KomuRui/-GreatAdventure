#include "PigEnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//�X�V
void PigEnemyRotationState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void PigEnemyRotationState::Update3D(Enemy* enemy)
{
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void PigEnemyRotationState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyRotationState::Enter(Enemy* enemy)
{
}