#include "PlayerStateManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Player/PlayerBase.h"


//�estatic�ϐ��̏�����
JumpingState* PlayerStateManager::playerJumping_ = new JumpingState;
JumpRotationningState* PlayerStateManager::playerJumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerStateManager::playerRotationning_ = new RotationningState;
RunningState* PlayerStateManager::playerRunning_ = new RunningState;
StandingState* PlayerStateManager::playerStanding_ = new StandingState;
WalkingState* PlayerStateManager::playerWalking_ = new WalkingState;
PlayerState* PlayerStateManager::playerState_ = playerStanding_;

////�萔
namespace
{
    const float RUN_SPEED = 1.5f;                 // GetPrivateProfilefloat("PLAYER", "RunSpeed", "0.02", ".\\/Parameter/Player/PlayerParameter.ini");//�����Ă���Ƃ��̃L�����̃X�s�[�h
    const float PLAYER_WALK_ANIM_SPEED = 1.0f;    //�A�j���[�V�����̍Đ����x
    const float ANIM_RUN_SPEED = 2.0f;            //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
}

//�R���X�g���N�^
PlayerStateManager::PlayerStateManager():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//�X�V
void PlayerStateManager::Update2D(PlayerBase* player)
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;
    
    if (PadLx > ZERO || PadLx < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(player->GethModel(), true)
                                         : Model::SetAnimFlag(player->GethModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (!player->IsRotation())
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            player->SetAngle(-atan2(PadLx, -padLy));
            player->SetJampRotationPreviousAngle(player->GetAngle());
        }
        else
            player->SetJampRotationPreviousAngle(-atan2(PadLx, padLy));


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(player->GethModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(player->GethModel(), PLAYER_WALK_ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (!player->IsRotation())
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmmRotate()))));
            else
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmPreviousAngle()))));

            //Z�̃|�W�V��������0�ɂ���
            player->SetPositionZ(ZERO);

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(player->GethModel(), false);

	//���݂̏�Ԃ̍X�V���Ă�
	playerState_->Update2D(player);
}

//3D�p�X�V
void PlayerStateManager::Update3D(PlayerBase* player)
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //�����ł��������Ȃ�
    if (PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        playerState_ == PlayerStateManager::playerStanding_ ? Model::SetAnimFlag(player->GethModel(), true)
                                         : Model::SetAnimFlag(player->GethModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (!player->IsRotation())
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            player->SetAngle(atan2(PadLx, padLy) + player->GetCamAngle());
            player->SetJampRotationPreviousAngle(player->GetAngle());
        }
        else
            player->SetJampRotationPreviousAngle(atan2(PadLx, padLy) + player->GetCamAngle());


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(player->GethModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(player->GethModel(), PLAYER_WALK_ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (!player->IsRotation())
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmmRotate()))));
            else
                player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(XMVector3TransformCoord(front_ / 10, player->GetmPreviousAngle()))));

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(player->GethModel(), false);

    //���݂̏�Ԃ̍X�V���Ă�
    playerState_->Update3D(player);
}

//���͂ɂ���ď�ԕω�����
void PlayerStateManager::HandleInput(PlayerBase* player)
{
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PlayerStateManager::Enter(PlayerBase* player)
{
}
