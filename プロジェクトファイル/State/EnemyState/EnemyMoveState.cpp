#include "EnemyMoveState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "../../Enemy/Enemy.h"

//�X�V
void EnemyMoveState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyMoveState::Update3D(Enemy* enemy)
{
    //�ړ�
	enemy->Move();

     //��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        //��Ԃ���]�ɐݒ�
        enemy->ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //�A�j���[�V������~
        Model::SetAnimFlag(enemy->GetModelNumber(), false);
    }

    //��ԕb�����₷
    stateCount_++;

	//���͏���
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