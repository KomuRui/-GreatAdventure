#include "EnemyRotationState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "../../Enemy/Enemy.h"

//�萔
namespace
{
    static const float ADD_ROTATION_ANGLE = 0.02f; //��]����Ƃ��̉��Z����p�x
}

//�X�V
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//���͏���
	HandleInput(enemy);
}

//3D�p�X�V
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//��]
	enemy->Rotation();

    //�㎲������]�����ăZ�b�g
    enemy->SetAngle(enemy->GetAngle() + (ADD_ROTATION_ANGLE * rotationSign_));

    //��]�p�x����]�����������Ȃ�����
    if (rotationTotal_ > rotationAngle_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //��Ԃ�ҋ@�ɐݒ�
        enemy->ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
    }

	//���͏���
	HandleInput(enemy);
}

//���͂ɂ���ď�ԕω�����
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void EnemyRotationState::Enter(Enemy* enemy)
{
    rotationSign_ = rand() % 2 == 1 ? 1 : -1;
    rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
}