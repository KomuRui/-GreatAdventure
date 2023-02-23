#include "PlayerMiniGame.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Block/Block.h"
#include "../Engine/ResourceManager/Image.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"

//�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float GRAVITY_ADDITION = 0.03f;                                                                  //�d�͂̉��Z�l
    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);   //�A�j���[�V�����̍Đ����x

    ////////////////�J����///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //�V�����_�[�ŃJ�������삷�鎞�̉��Z����l
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //�X�e�B�b�NR�ŃJ�����𑀍삷��Ƃ��̉��Z����l
}

//�R���X�g���N�^
PlayerMiniGame::PlayerMiniGame(GameObject* parent)
    :PlayerBase(parent), hPictWind_(ZERO), hPictWind2_(ZERO)
{
}

//������
void PlayerMiniGame::ChildPlayerInitialize()
{
    //��ԌW����ύX
    ARGUMENT_INITIALIZE(normalInterpolation_, 0.3f);

    //////���̉摜�����[�h

    //1
    hPictWind_ = Image::Load("Image/MiniGame/kaze1.png");
    assert(hPictWind_ >= ZERO);

    //2
    hPictWind2_ = Image::Load("Image/MiniGame/kaze2.png");
    assert(hPictWind2_ >= ZERO);


    //�~�j�Q�[���̎��̃J�����̈ʒu�͏����Ⴄ�̂Őݒ�
    ARGUMENT_INITIALIZE(camVec_[LONG],XMVectorSet(ZERO, 5, -55, ZERO));
    ARGUMENT_INITIALIZE(camVec_[SHORT],XMVectorSet(ZERO, 5, -15, ZERO));
    ARGUMENT_INITIALIZE(vCam_, camVec_[SHORT]);
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void PlayerMiniGame::ChildPlayerStartUpdate()
{
}

//�X�V
void PlayerMiniGame::ChildPlayerUpdate()
{
    MovingOperation();       //Player����
    RotationInStage();       //�X�e�[�W�ɍ��킹�ĉ�]
    StageRayCast();          //�X�e�[�W�Ƃ̓����蔻��
}

//�`��
void PlayerMiniGame::ChildDraw()
{
    //�������郂�[�h�Ȃ�
    if (MiniGameManager::IsRunMode() && IsCamLong())
    {
        Transform t;

        //�����ŕ\������摜��ς���
        if (rand() % 2 == 1)
        {
            Image::SetTransform(hPictWind_, t);
            Image::Draw(hPictWind_);
        }
        else
        {
            Image::SetTransform(hPictWind2_, t);
            Image::Draw(hPictWind2_);
        }
    }
}

//�v���C���[����
void PlayerMiniGame::MovingOperation()
{
    //���̏�Ԃ̓���
    pState_->UpdateMiniGame(this);
}

//�X�e�[�W�ɍ��킹�ĉ�]
void PlayerMiniGame::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = ZERO;

    //�O�ς̌��ʓ����p
    XMVECTOR cross;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (TwoVectorNotValue(up_, vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));

        //�O�ς����߂�(���̌��ʂ̎��������ɂ���)
        cross = XMVector3Cross(up_, vNormal_);
    }
    else
        cross = XMVectorSet(ZERO, ZERO, ZERO, ZERO);

    //�G���[�͈͓̔��ł͂Ȃ����
    if (dotX != ZERO && dotX <= 1 && dotX >= -1 && !VectorNotZero(cross))
    {

        //Player����]�����邽�߂ɓ�̎��ŉ�]������
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //�J�����̍s��p��
        ARGUMENT_INITIALIZE(camMat_, totalMx_);
    }
    else
    {
        //Player����]�����邽�߂Ɏ��ŉ�]������
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
    }

    //���g�̏�x�N�g���X�V
    ARGUMENT_INITIALIZE(up_, vNormal_);
}

//Player�̃J�����̏���
void PlayerMiniGame::PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar)
{
    //���郂�[�h�Ȃ�
    if (MiniGameManager::IsRunMode()) RunModeCameraBehavior();


    XMFLOAT3 camPos;                                             //�ŏI�I�ȃJ�����̈ʒu������ϐ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);         //transform_.position_��Vector�^
    XMVECTOR vCamDis_ = XMVector3TransformCoord(vCam_, camMat_); //vCam����

    vPos += vCamDis_;                //Player��Pos��Player����J�����̃x�N�g��������
    XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

    *tar = Float3Add(transform_.position_, VectorToFloat3(vNormal_ * 3));

    //�J�����̂��낢��ݒ�
    Camera::SetUpDirection(vNormal_);
    Camera::SetPosition(camPos);
    Camera::SetTarget(*tar);

    //���C�g�̈ʒu�ݒ�
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//���C�œ����蔻��
void PlayerMiniGame::StageRayCast()
{
    //�e����
    RayCastData straightData;
    RayCastData downData;

    //�������Ă邩�m�F
    HitTest(&straightData, STRAIGHT_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    ////////////////////////////////�͂ݏo������������//////////////////////////////////////

    //��Ƀx�N�g���^�̃|�W�V����������Ă���
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //�O
    if (straightData.dist <= 1.0)
    {
        //��Q�����nullptr����Ȃ��̂Ȃ玀�S
        if (straightData.obstacle != nullptr)
        {
            //���������G�폜
            straightData.obstacle->KillMe();

            //���S��Ԃ���Ȃ��̂Ȃ�
            if (PlayerStateManager::playerState_ != PlayerStateManager::playerDieing_)
            {
                pState_->ChangeState(PlayerStateManager::playerDieing_, this);
            }
        }

        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //��
    if (downData.dist >= 1.0)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((down_ / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //��]����Ȃ������S���Ă��Ȃ��̂Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_ && PlayerStateManager::playerState_ != PlayerStateManager::playerDieing_)
        {
            //��ԕύX
            pState_->ChangeState(PlayerStateManager::playerStanding_, this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
}

//�����蔻��
void PlayerMiniGame::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;                                               //���C�̔��ˈʒu  
    XMStoreFloat3(&data->dir, XMVector3TransformCoord(dir, transform_.mmRotate_));    //���C�̕���
    Model::AllRayCast(hGroundModel_, data);                                           //���C�𔭎�
}

//�������[�h�̎��̃J�����̏���
void PlayerMiniGame::RunModeCameraBehavior()
{
    //�J�������������Ȃ�
    if (camStatus_ == LONG)
    {
        //�J�������Ԃœ�����
        ARGUMENT_INITIALIZE(vCam_, XMVectorLerp(vCam_, camVec_[camStatus_], 0.1f));

        //������1�ȓ��Ȃ�
        if (RangeCalculation(vCam_, camVec_[camStatus_]) < 1.0f)
        {
            ARGUMENT_INITIALIZE(camStatus_, SHORT);
            MiniGameManager::ResetRunSpeed();
            MiniGameManager::SetComboTextScale(1.0f);
        }
    }
    //�ʏ�ɂ���
    else
    {
        //�J�������Ԃœ�����
        ARGUMENT_INITIALIZE(vCam_, XMVectorLerp(vCam_, camVec_[camStatus_], 0.1f));

        //������1�ȓ��Ȃ�
        if (RangeCalculation(vCam_, camVec_[camStatus_]) < 1.0f)
        {
            ARGUMENT_INITIALIZE(vCam_, camVec_[camStatus_]);
            MiniGameManager::SetRunMode(false);
            MiniGameManager::ResetCombo();
        }
    }
}

//�����ɓ�������
void PlayerMiniGame::OnCollision(GameObject* pTarget)
{
    //�؂̓G�Ɠ�����������]���Ă��Ȃ��̂Ȃ�
    if (pTarget->GetObjectName() == "MiniGamePigEnemy" && !IsRotation())
    {
        //���������G�폜
        pTarget->KillMe();

        //���S��Ԃ���Ȃ��̂Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerDieing_)
        {
            pState_->ChangeState(PlayerStateManager::playerDieing_,this);
        }
    }
}