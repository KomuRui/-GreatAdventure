#include "PlayerState.h"
#include "../Engine/GameManager.h"
#include "../Engine/Model.h"

//�estatic�ϐ��̏�����
JumpingState* PlayerState::jumping_ = new JumpingState;
JumpRotationningState* PlayerState::jumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerState::rotationning_ = new RotationningState;
RunningState* PlayerState::running_ = new RunningState;
StandingState* PlayerState::standing_ = new StandingState;
WalkingState* PlayerState::walking_ = new WalkingState;
State* PlayerState::state_ = standing_;


//�R���X�g���N�^
PlayerState::PlayerState():front_(XMVectorSet(0, 0, 1.0f, 0))
{
}

//�X�V
void PlayerState::Update2D()
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if (PadLx > ZERO || PadLx < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        state_ == PlayerState::standing_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            GameManager::GetpPlayer()->SetAngle(-atan2(PadLx, -padLy));
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(-atan2(PadLx, padLy));


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //Z�̃|�W�V��������0�ɂ���
            GameManager::GetpPlayer()->SetPositionZ(ZERO);

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));

        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

	//���݂̏�Ԃ̍X�V���Ă�
	state_->Update2D();
}

//3D�p�X�V
void PlayerState::Update3D()
{
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    //�����ł��������Ȃ�
    if (PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
    {
        //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
        state_ == PlayerState::standing_ ? Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), true)
                                         : Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

        //�W�����v��]�����Ă��Ȃ��Ȃ�
        if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
        {
            //�L�����̏㎲�̊p�x���R���g���[���[�̊p�x�ɕϊ�
            GameManager::GetpPlayer()->SetAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(GameManager::GetpPlayer()->GetAngle());
        }
        else
            GameManager::GetpPlayer()->SetJampRotationPreviousAngle(atan2(PadLx, padLy) + GameManager::GetpPlayer()->GetCamAngle());


        //Player�̈ړ�
        {

            //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
            if (Input::GetPadTrrigerL())
            {
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_RUN_SPEED);
                front_ = XMVector3Normalize(front_) * RUN_SPEED;
            }
            else
                Model::SetAnimSpeed(GameManager::GetpPlayer()->GetPlayerhModel(), ANIM_SPEED);


            //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
            if (state_ != PlayerState::jumpRotationning_ && state_ != PlayerState::rotationning_)
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmmRotate()))));
            else
                GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, GameManager::GetpPlayer()->GetmPreviousAngle()))));

            //�O�x�N�g���̏�����
            ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
        }
    }
    else
        Model::SetAnimFlag(GameManager::GetpPlayer()->GetPlayerhModel(), false);

    //���݂̏�Ԃ̍X�V���Ă�
    state_->Update3D();
}

//���͂ɂ���ď�ԕω�����
void PlayerState::HandleInput()
{
	//���݂̏�Ԃ̓��͏������Ă�
	state_->HandleInput();
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void PlayerState::Enter()
{
	//���݂̏�Ԃ�Enter�֐����Ă�
	state_->Enter();

}
