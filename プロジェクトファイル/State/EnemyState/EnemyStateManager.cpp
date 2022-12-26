#include "EnemyStateManager.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Enemy/Enemy.h"

//�estatic�ϐ��̏�����
EnemyDieState* EnemyStateManager::EnemyDie_ = new EnemyDieState;
EnemyKnockBackState* EnemyStateManager::EnemyKnockBack_ = new EnemyKnockBackState;
EnemyMoveState* EnemyStateManager::EnemyMove_ = new EnemyMoveState;
EnemyRotationState* EnemyStateManager::EnemyRotation_ = new EnemyRotationState;
EnemyWaitState* EnemyStateManager::EnemyWait_ = new EnemyWaitState;

//�R���X�g���N�^
EnemyStateManager::EnemyStateManager()
{
}

//�X�V
void EnemyStateManager::Update2D(Enemy* enemy)
{
    //���݂̏�Ԃ̍X�V���Ă�
    //EnemyState_->Update2D(enemy);
}

//3D�p�X�V
void EnemyStateManager::Update3D(Enemy* enemy)
{
    //���݂̏�Ԃ̍X�V���Ă�
    //EnemyState_->Update3D(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyStateManager::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyStateManager::Enter(Enemy* enemy)
{
}
