#include "EnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "EnemyStateManager.h"

//�X�V
void EnemyWaitState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyWaitState::Update3D(Enemy* enemy)
{

    //enemy->
    ////��Ԏ��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    //if (stateCount_ > operationTime_)
    //{
    //    //0�ɏ�����
    //    ZERO_INITIALIZE(operationTime_);

    //    //��Ԃ�Move�ɕύX
    //    PigEnemyStateManager::pigEnemyState_ = PigEnemyStateManager::pigEnemyMove_;
    //    PigEnemyStateManager::pigEnemyState_->Enter(enemy);
    //}

	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyWaitState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyWaitState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 13 + 6) * 10;
	ZERO_INITIALIZE(stateCount_);
}