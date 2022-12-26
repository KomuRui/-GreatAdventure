#include "PigEnemyWaitState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PigEnemyStateManager.h"

//�X�V
void PigEnemyWaitState::Update2D(Enemy* enemy)
{
	HandleInput(enemy);
}

//3D�p�X�V
void PigEnemyWaitState::Update3D(Enemy* enemy)
{
    //��Ԏ��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);

        //��Ԃ�Move�ɕύX
        PigEnemyStateManager::pigEnemyState_ = PigEnemyStateManager::pigEnemyMove_;
        PigEnemyStateManager::pigEnemyState_->Enter(enemy);
    }

	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void PigEnemyWaitState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyWaitState::Enter(Enemy* enemy)
{
	operationTime_ = (rand() % 13 + 6) * 10;
	ZERO_INITIALIZE(stateCount_);
}