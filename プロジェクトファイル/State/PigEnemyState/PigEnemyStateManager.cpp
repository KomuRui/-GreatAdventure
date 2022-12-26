#include "PigEnemyStateManager.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"

//�estatic�ϐ��̏�����
PigEnemyDieState* PigEnemyStateManager::pigEnemyDie_ = new PigEnemyDieState;
PigEnemyKnockBackState* PigEnemyStateManager::pigEnemyKnockBack_ = new PigEnemyKnockBackState;
PigEnemyMoveState* PigEnemyStateManager::pigEnemyMove_ = new PigEnemyMoveState;
PigEnemyRotationState* PigEnemyStateManager::pigEnemyRotation_ = new PigEnemyRotationState;
PigEnemyWaitState* PigEnemyStateManager::pigEnemyWait_ = new PigEnemyWaitState;
EnemyState* PigEnemyStateManager::pigEnemyState_ = pigEnemyWait_;

//�R���X�g���N�^
PigEnemyStateManager::PigEnemyStateManager()
{
}

//�X�V
void PigEnemyStateManager::Update2D(Enemy* enemy)
{
    //���݂̏�Ԃ̍X�V���Ă�
    pigEnemyState_->Update2D(enemy);
}

//3D�p�X�V
void PigEnemyStateManager::Update3D(Enemy* enemy)
{
    //���݂̏�Ԃ̍X�V���Ă�
    pigEnemyState_->Update3D(enemy);
}

//���͂ɂ���ď�ԕω�����
void PigEnemyStateManager::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyStateManager::Enter(Enemy* enemy)
{
}
