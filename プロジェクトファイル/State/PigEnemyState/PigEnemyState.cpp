#include "PigEnemyState.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Model.h"

//�estatic�ϐ��̏�����
PigEnemyDieState* PigEnemyState::pigEnemyDie_ = new PigEnemyDieState;
PigEnemyKnockBackState* PigEnemyState::pigEnemyKnockBack_ = new PigEnemyKnockBackState;
PigEnemyMoveState* PigEnemyState::pigEnemyMove_ = new PigEnemyMoveState;
PigEnemyRotationState* PigEnemyState::pigEnemyRotation_ = new PigEnemyRotationState;
PigEnemyWaitState* PigEnemyState::pigEnemyWait_ = new PigEnemyWaitState;
State* PigEnemyState::pigEnemyState_ = pigEnemyWait_;

//�R���X�g���N�^
PigEnemyState::PigEnemyState()
{
}

//�X�V
void PigEnemyState::Update2D()
{
    //���݂̏�Ԃ̍X�V���Ă�
    pigEnemyState_->Update2D();
}

//3D�p�X�V
void PigEnemyState::Update3D()
{
    //���݂̏�Ԃ̍X�V���Ă�
    pigEnemyState_->Update3D();
}

//���͂ɂ���ď�ԕω�����
void PigEnemyState::HandleInput()
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PigEnemyState::Enter()
{
}
