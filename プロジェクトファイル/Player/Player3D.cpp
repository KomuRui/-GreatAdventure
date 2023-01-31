#include "Player3D.h"
#include "../Engine/Camera.h"
#include "../Engine/Light.h"
#include "../Block/Block.h"


//�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float GRAVITY_ADDITION = 0.03f;    //�d�͂̉��Z�l

    ////////////////�J����///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //�V�����_�[�ŃJ�������삷�鎞�̉��Z����l
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //�X�e�B�b�NR�ŃJ�����𑀍삷��Ƃ��̉��Z����l
}

//�R���X�g���N�^
Player3D::Player3D(GameObject* parent)
	:PlayerBase(parent)
{
}

//�X�V
void Player3D::ChildPlayerUpdate()
{
    MovingOperation();       //Player����
    RotationInStage();       //�X�e�[�W�ɍ��킹�ĉ�]
    StageRayCast();          //�X�e�[�W�Ƃ̓����蔻��
}

//�v���C���[����
void Player3D::MovingOperation()
{
    //���̏�Ԃ̓���
    pState_->Update3D(this);

    //B����������J�����̈ʒu�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        //�J�����̏�ԕύX
        camStatus_ = (camStatus_ == LONG) ? SHORT
            : LONG;
    }

    //���V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += CAM_SHOULDER_ADD_VALUE;

    //�E�V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= CAM_SHOULDER_ADD_VALUE;

    //�E�X�e�B�b�N�ŃJ�����̊p�x������
    if (Input::GetPadStickR().x) camAngle_ += CAM_STICR_ADD_VALUE * Input::GetPadStickR().x;
}

//�X�e�[�W�ɍ��킹�ĉ�]
void Player3D::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = ZERO;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (TwoVectorNotValue(up_,vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));
    }

    //�G���[�͈͓̔��ł͂Ȃ����
    if (dotX != ZERO && dotX <= 1 && dotX >= -1)
    {
        //�O�ς����߂�(���̌��ʂ̎��������ɂ���)
        XMVECTOR cross = XMVector3Cross(up_, vNormal_);

        //Player����]�����邽�߂ɓ�̎��ŉ�]������
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (IsRotation()) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //�J�����̍s��p��
        ARGUMENT_INITIALIZE(camMat_,totalMx_);
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
    ARGUMENT_INITIALIZE(up_,vNormal_);
}

//Player�̃J�����̏���
void Player3D::PlayerCameraBehavior(XMFLOAT3* pos, XMFLOAT3* tar)
{
    XMFLOAT3 camPos;                                         //�ŏI�I�ȃJ�����̈ʒu������ϐ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_��Vector�^
    vCam_ = camVec_[camStatus_];                             //Player����J�����̃x�N�g�����쐬
    vCam_ = XMVector3TransformCoord(vCam_, camMat_);         //vCam����
    vCam_ = XMVector3TransformCoord(vCam_, XMMatrixRotationAxis(vNormal_, camAngle_));

    vPos += vCam_;                   //Player��Pos��Player����J�����̃x�N�g��������
    XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

    //��Ԉړ�
    XMStoreFloat3(tar, XMVectorLerp(XMLoadFloat3(tar), XMLoadFloat3(&transform_.position_), CAMERA_INTERPOLATION_FACTOR));

    //flag��true�Ȃ�ʒu������
    if (isMoveCamPos_)
        XMStoreFloat3(pos, XMVectorLerp(XMLoadFloat3(pos), XMLoadFloat3(&camPos), CAMERA_INTERPOLATION_FACTOR));

    //�J�����̂��낢��ݒ�
    Camera::SetUpDirection(vNormal_);
    Camera::SetPosition(*pos);
    Camera::SetTarget(*tar);

    //���C�g�̈ʒu�ݒ�
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//���C�œ����蔻��
void Player3D::StageRayCast()
{
    //�e����
    RayCastData rightData;
    RayCastData leftData;
    RayCastData straightData;
    RayCastData upData;
    RayCastData downData;

    //�������Ă邩�m�F
    HitTest(&rightData, RIGHT_VECTOR);
    HitTest(&leftData, LEFT_VECTOR);
    HitTest(&straightData, STRAIGHT_VECTOR);
    HitTest(&upData, UP_VECTOR);
    HitTest(&downData, DOWN_VECTOR);

    ////////////////////////////////�͂ݏo������������//////////////////////////////////////

    //��Ƀx�N�g���^�̃|�W�V����������Ă���
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //�E
    if (rightData.dist <= 1.0)
    {
        XMVECTOR dis = { rightData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(RIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //��
    if (leftData.dist <= 1.0)
    {
        XMVECTOR dis = { -leftData.dist,ZERO,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(LEFT_VECTOR, transform_.mmRotate_) - dis));
    }

    //�O
    if (straightData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));
    }

    //��
    if (upData.dist <= 1.0)
    {
        XMVECTOR dis = { ZERO,upData.dist,ZERO };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (XMVector3TransformCoord(UP_VECTOR, transform_.mmRotate_) - dis));

        //��ԕύX
        ARGUMENT_INITIALIZE(PlayerStateManager::playerState_, PlayerStateManager::playerStanding_);
        PlayerStateManager::playerState_->Enter(this);

        //�u���b�N���nullptr����Ȃ��̂Ȃ�
        if (upData.block != nullptr)
        {
            //�u���b�N�𓖂����Ă����Ԃɂ���
            upData.block->SetIsHit(true);
        }
    }

    //��
    if (downData.dist >= 1.0)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((down_ / 10) * acceleration_));
        acceleration_ += GRAVITY_ADDITION;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerStateManager::playerState_ != PlayerStateManager::playerRotationning_)
        {
            //��ԕύX
            PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
            PlayerStateManager::playerState_->Enter(this);
        }

        ARGUMENT_INITIALIZE(acceleration_, 1);
    }
}

//�����蔻��
void Player3D::HitTest(RayCastData* data, const XMVECTOR& dir)
{
    data->start = transform_.position_;                                               //���C�̔��ˈʒu  
    XMStoreFloat3(&data->dir, XMVector3TransformCoord(dir, transform_.mmRotate_));    //���C�̕���
    Model::AllRayCast(hGroundModel_, data);                                           //���C�𔭎�
}

