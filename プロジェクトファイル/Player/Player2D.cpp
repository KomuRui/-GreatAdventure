#include "Player2D.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"
#include "../Engine/ResourceManager/Audio.h"

//�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float GRAVITY_ADDITION = 0.03f;    //�d�͂̉��Z�l
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //Player��X�̃��f���T�C�Y
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //Player��Y�̃��f���T�C�Y

    ////////////////���C�g///////////////////

    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //���C�g��Z�̃|�W�V����

    ////////////////�J����///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2D�̎��̃J������Z�̈ʒu
}

//�R���X�g���N�^
Player2D::Player2D(GameObject* parent)
    :PlayerBase(parent)
{
}

//�X�V
void Player2D::ChildPlayerUpdate()
{
    RotationInStage();       //�X�e�[�W�ɍ��킹�ĉ�]
    MovingOperation();       //Player����
    StageRayCast();          //�X�e�[�W�Ƃ̓����蔻��
}

//�v���C���[����
void Player2D::MovingOperation()
{
    //���̏�Ԃ̓���
    pState_->Update2D(this);
}

//�X�e�[�W�ɍ��킹�ĉ�]
void Player2D::RotationInStage()
{
    //Player�̌����̊p�x�����x�N�g������]������
    ARGUMENT_INITIALIZE(transform_.mmRotate_,XMMatrixRotationAxis(UP_VECTOR, angle_));

    //Player����]���Ă���Ȃ�
    if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(UP_VECTOR, jampRotationPreviousAngle_));
}

//Player�̃J�����̏���
void Player2D::PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar)
{
    //�ŏI�I�Ȉʒu�ƃ^�[�Q�b�g
    XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
    XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, CAM_POS_2D_Z };

    //flag��true�Ȃ�ʒu������
    if (isMoveCamPos_)
        XMStoreFloat3(pos, XMVectorLerp(XMLoadFloat3(pos), XMLoadFloat3(&camPos2), CAMERA_INTERPOLATION_FACTOR));

    XMStoreFloat3(tar, XMVectorLerp(XMLoadFloat3(tar), XMLoadFloat3(&camTar2), CAMERA_INTERPOLATION_FACTOR));

    //�J�����̂��낢��ݒ�
    Camera::SetPosition(*pos);
    Camera::SetTarget(*tar);

    //Player�ɂ��Ă郉�C�g�̈ʒu����
    Light::SetPlayerPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, LIGHT_POS_Z, ZERO));
}

//���C�œ����蔻��
void Player2D::StageRayCast()
{
    //�u���b�N�Ƃ̓����蔻������邽�߂Ƀg�����X�t�H�[����ۑ�
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= (PLAYER_MODEL_SIZE_X / 2);

    //�E
    if (GameManager::GetpStage()->IsBlock(&Colpos, Right))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.x += (PLAYER_MODEL_SIZE_X / 2);

    //��
    if (pstage_->IsBlock(&Colpos, Left))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);
    }

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.y -= (PLAYER_MODEL_SIZE_Y / 2);

    //��
    if (pstage_->IsBlock(&Colpos, Under))
    {
        //�|�W�V�����ݒ�
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);

        //�����O�񒅒n���Ă��Ȃ������特�炷
        if (!isBeforeLand_)
        {
            ARGUMENT_INITIALIZE(isBeforeLand_, true);
            PlayerAudioManager::JumpLandAudio();
        }

        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //��ԕύX
            ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
    else
        ARGUMENT_INITIALIZE(isBeforeLand_, false);

    ARGUMENT_INITIALIZE(Colpos, transform_.position_);
    Colpos.y += (PLAYER_MODEL_SIZE_Y / 2);

    //��
    if (pstage_->IsBlock(&Colpos, Top))
    {
        ARGUMENT_INITIALIZE(transform_.position_, Colpos);

        //��ԕύX
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }

    //�e����
    RayCastData rightData;
    RayCastData leftData;
    RayCastData upData;
    RayCastData downData;

    //�������Ă邩�m�F
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    if (rightData.dist <= 1)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (RIGHT_VECTOR - dis));
    }
    if (leftData.dist <= 1)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (LEFT_VECTOR - dis));
    }

    if (upData.dist <= 1)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (UP_VECTOR - dis));
    }

    if (downData.dist >= 0.9)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((DOWN_VECTOR / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            PlayerAudioManager::JumpLandAudio();

            //��ԕύX
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }

}

//�����蔻��
void Player2D::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;       //���C�̔��ˈʒu  
    XMStoreFloat3(&data->dir, dir);           //���C�̕���
    Model::RayCast(hGroundModel_, data);      //���C�𔭎�                                      
}

