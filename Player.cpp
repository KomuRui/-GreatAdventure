#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"
#include "Engine/GameManager.h"
#include <algorithm>
#include <iostream>

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), 

    ///////////////�L�����̕K�v�ȏ��///////////////////

    //���f��
    hModel_(-1),
    hGroundModel_(0),

    //�e�����x�N�g��
    vNormal_(XMVectorSet(0, -1, 0, 0)),
    up_(XMVectorSet(0, 1, 0, 0)),
    down_(XMVectorSet(0, -1, 0, 0)),
    front_(XMVectorSet(0, 0, 1, 0)),

    //�L�����̎���]�ɕK�v�ȕϐ�
    totalMx_(XMMatrixIdentity()),
    jampRotationPreviousAngle_(0),
    angle_(0),
    normalFlag_(true),

    //�W�����v
    vJamp_(XMVectorSet(0, 0, 0, 0)),
    isJampRotation_(false),
    isJamp_(false),

    //���̑�
    acceleration_(1),
    isFly_(false),
    isRotation_(false),
    pState_(new PlayerState),

    ///////////////////�J����///////////////////////

    camMat_(XMMatrixIdentity()),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true)
    
{
    camVec_[LONG] = XMVectorSet(0.0f, 15, -15, 0.0f);
    camVec_[SHORT] = XMVectorSet(0.0f, 4, -4, 0.0f);
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Player::Initialize()
{
    ///////////////Player�̏�ԏ�����///////////////////

    PlayerState::state_ = PlayerState::standing_;

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= ZERO);

    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

    ///////////////Player�̓����蔻��ݒ�///////////////////

    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    ///////////////�G�t�F�N�g�ƃA�j���[�V�����ݒ�///////////////////

    //�G�t�F�N�g�o�����߂ɕK�v�ȃN���X
    pParticle_ = Instantiate<Particle>(this);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = GameManager::GetpStage();
    hGroundModel_ = pstage_->GethModel();

    //���g�̃|�W�V�����Z�b�g
    transform_.position_ = pstage_->GetPos();

    //���C���΂��Ď��g�̎���ݒ肷��
    RayCastData dataNormal;
    dataNormal.start = transform_.position_;      
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, down_);
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);   

    //���g�̏㎲�ݒ�
    vNormal_ = XMLoadFloat3(&dataNormal.normal);

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Player::StartUpdate()
{
}

//�X�V
void Player::Update()
{
    //�X�e�[�W���null�Ȃ炱�̐�͎��s���Ȃ�
    if (pstage_ == nullptr) return;

    //���C��^���ɑł�
    RayCastData data[MAX_RAY_SIZE];                        
    data[Under].start = transform_.position_;              
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, down_);
    data[Under].dir = moveY2;
    Model::BlockRayCast(hGroundModel_, &data[Under]);      

    //�^���̖@���𒲂ׂ�
    CheckUnderNormal(data);

    //�X�e�[�W��3D�Ȃ�
    if (pstage_->GetthreeDflag())
    {
        MovingOperation(data);   //Player����
        RotationInStage();       //�X�e�[�W�ɍ��킹�ĉ�]
        StageRayCast(data);      //�X�e�[�W�Ƃ̓����蔻��
    }
    //�X�e�[�W���^��2D�Ȃ�
    else
    {
        MovingOperation2D(data); //Player����
        RotationInStage2D();     //�X�e�[�W�ɍ��킹�ĉ�]
        StageRayCast2D();    //�X�e�[�W�Ƃ̓����蔻��
    }

    //�J�����̋���
    CameraBehavior();
} 

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

/////////////////////�֐�//////////////////////

//�J�����̏���
void Player::CameraBehavior()
{
    static XMFLOAT3 camTar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    if (pstage_->GetthreeDflag())
    {
        XMFLOAT3 camPos;                                         //�ŏI�I�ȃJ�����̈ʒu������ϐ�
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_��Vector�^
        XMVECTOR vCam = camVec_[camStatus_];                     //Player����J�����̃x�N�g�����쐬
        vCam = XMVector3TransformCoord(vCam, camMat_);            //vCam����
        vCam = XMVector3TransformCoord(vCam, XMMatrixRotationAxis(vNormal_, camAngle_));

        vPos += vCam;                    //Player��Pos��Player����J�����̃x�N�g��������
        XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

        //�J�����̏���������߂邽�߂�StagePotision�������ď�����̃x�N�g�����쐬
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal_), XMVectorGetY(-vNormal_), XMVectorGetZ(-vNormal_) };

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&transform_.position_), CAMERA_INTERPOLATION_FACTOR));

        if (camPosFlag_)
            XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos), CAMERA_INTERPOLATION_FACTOR));

        //�J�����̂��낢��ݒ�
        Camera::SetUpDirection(vNormal_);
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);

        //���C�g�ݒ�
        XMFLOAT3 lightPos;
        XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));

        Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
    }
    else
    {

        XMFLOAT3 camTar2 = { transform_.position_.x,transform_.position_.y,transform_.position_.z };
        XMFLOAT3 camPos2 = { transform_.position_.x, transform_.position_.y, CAM_POS_2D_Z };

        //flag��true�Ȃ�ʒu������
        if (camPosFlag_)
            XMStoreFloat3(&campos, XMVectorLerp(XMLoadFloat3(&campos), XMLoadFloat3(&camPos2), CAMERA_INTERPOLATION_FACTOR));

        XMStoreFloat3(&camTar, XMVectorLerp(XMLoadFloat3(&camTar), XMLoadFloat3(&camTar2), CAMERA_INTERPOLATION_FACTOR));

        //�J�����̂��낢��ݒ�
        Camera::SetPosition(campos);
        Camera::SetTarget(camTar);
       
        //Player�ɂ��Ă郉�C�g�̈ʒu����
        Light::SetPlayerPosition(XMFLOAT4(transform_.position_.x, transform_.position_.y, LIGHT_POS_Z, ZERO));
    }

}

//�^���̖@���𒲂ׂ�
void Player::CheckUnderNormal(RayCastData* data)
{
    //�@���𒲂ׂ邩�ǂ�����Flag��true�Ȃ�
    if (normalFlag_)
    {
        //���C���������Ă��Ă������ł���x�N�g����vNormal_�̒l���Ⴄ�̂Ȃ�
        if (data[Under].hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)))))
        {
            //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
            float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)), XMVector3Normalize(vNormal_)));

            //�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
            if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
            {
                //������ƕ��
                vNormal_ = XMVector3Normalize((XMVectorLerp( XMVector3Normalize(vNormal_), XMLoadFloat3(&data[Under].normal), NORMAL_INTERPOLATION_FACTOR)));
                down_ = -vNormal_;
            }

        }
    }
}

//�X�e�[�W�ɍ��킹��Player����](3D�p)
void Player::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_)));
    }

    //�O�ς����߂�(���̌��ʂ̎��������ɂ���)
    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    if (dotX != 0 && dotX <= 1 && dotX >= -1)
    {
        //Player����]�����邽�߂ɓ�̎��ŉ�]������
        totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (PlayerState::state_ == PlayerState::jumpRotationning_ || PlayerState::state_ == PlayerState::rotationning_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_);

        //�J�����̍s��p��
        camMat_ = totalMx_;
    }
    else
    {
        //Player����]�����邽�߂Ɏ��ŉ�]������
        transform_.mmRotate_ = totalMx_;
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        //Player����]���Ă���Ȃ�
        if (PlayerState::state_ == PlayerState::jumpRotationning_ || PlayerState::state_ == PlayerState::rotationning_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(vNormal_, jampRotationPreviousAngle_));
    }

    //���g�̏�x�N�g���X�V
    up_ = vNormal_;
}

//�X�e�[�W�ɍ��킹��Player����](2D�p)
void Player::RotationInStage2D()
{
    //Player�̌����̊p�x�����x�N�g������]������
    transform_.mmRotate_ = XMMatrixRotationAxis(UP_VECTOR, angle_);

    //Player����]���Ă���Ȃ�
    if (PlayerState::state_ == PlayerState::jumpRotationning_ || PlayerState::state_ == PlayerState::rotationning_) mPreviousAngle_ = (totalMx_ * XMMatrixRotationAxis(UP_VECTOR, jampRotationPreviousAngle_));
}

//�v���C���[����(3D�p)
void Player::MovingOperation(RayCastData* data)
{
   // float PadLx = Input::GetPadStickL().x;
   // float padLy = Input::GetPadStickL().y;
   // //�����ł��������Ȃ�
   // if(PadLx > ZERO || padLy > ZERO || PadLx < ZERO || padLy < ZERO)
   // {
   //     //����Player���������Ă��Ȃ��̂Ȃ�A�j���[�V�����J�n
   //     !isJampRotation_ && !isRotation_ && !isFly_  ? Model::SetAnimFlag(hModel_, true)
   //                                                  : Model::SetAnimFlag(hModel_, false);
   //     //��]�����Ă��Ȃ��Ȃ�
   //     if (!isJampRotation_ && !isRotation_)
   //     {
   //         angle_ = atan2(PadLx, padLy) + camAngle_;
   //         jampRotationPreviousAngle_ = angle_;
   //     }
   //     else
   //         jampRotationPreviousAngle_ = atan2(PadLx, padLy) + camAngle_;
   //     //�ړ�����Ƃ���L�g���K�[�������Ă�����_�b�V��������
   //     if (Input::GetPadTrrigerL())
   //     {
   //         Model::SetAnimSpeed(hModel_, ANIM_RUN_SPEED);
   //         front_ *= RUN_SPEED;
   //     }
   //     else
   //         Model::SetAnimSpeed(hModel_, ANIM_SPEED);
   //     //�W�����v��]�����Ă��邩�ɂ����Player�̓�������������,Player�ړ�
   //     transform_.position_ = (!isJampRotation_ && !isRotation_) ? Transform::Float3Add(transform_.position_,Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, transform_.mmRotate_)))
   //                                                               : Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3TransformCoord(front_ / 10, mPreviousAngle_)));
   //     //�O�x�N�g���̏�����
   //     ARGUMENT_INITIALIZE(front_, XMVector3Normalize(front_));
   // }
   // else
   //     Model::SetAnimFlag(hModel_, false);
   // //�����ł��Ȃ��̂Ȃ�
   // if (!isFly_)
   // {
   //     //��������������0.9f��菬�����Ȃ�
   //     if (data[Under].dist < 0.9f)
   //     {
   //         //�n�`�ɍ������킹��
   //         XMStoreFloat3(&transform_.position_, XMLoadFloat3(&data[Under].pos) + vNormal_);
   //         //�e�ϐ�������
   //         ARGUMENT_INITIALIZE(acceleration_, 1);
   //         ARGUMENT_INITIALIZE(isJampRotation_, false);
   //         ARGUMENT_INITIALIZE(isFly_, false);
   //     }
   // }
   // //���̏�Ԃ̓���
   //// pState_->Update();
   // //�����W�����v�����Ă��Ȃ���Ԃ�A�{�^�����������Ȃ�
   // if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isFly_)
   // {
   //     //�W�����v�̃x�N�g���E�t���O������
   //     ARGUMENT_INITIALIZE(vJamp_, (vNormal_) / 2);
   //     ARGUMENT_INITIALIZE(keepJamp_, vJamp_);
   //     ARGUMENT_INITIALIZE(isJamp_, true);
   //    ARGUMENT_INITIALIZE(isFly_, true);
   //     //�W�����v������dist����
   //     data[Under].dist++;   
   // }
   // //�����W�����v�����Ă��ĉ�]�����Ă��Ȃ���TrrigerR�������Ă�����
   // if (Input::GetPadTrrigerR() && !isJampRotation_ && isJamp_)
   // {
   //     //�W�����v�̃x�N�g���E��]�t���O������
   //     ARGUMENT_INITIALIZE(vJamp_, (vNormal_) / 2);
   //     ARGUMENT_INITIALIZE(keepJamp_, vJamp_);
   //     ARGUMENT_INITIALIZE(isJampRotation_, true);
   // }
   // //�����W�����v�����Ă�����
   // if (isJamp_)
   // {  
   //     //�����������Ȃ�
   //     if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
   //     {
   //         //Player�W�����v�ړ�
   //         transform_.position_ = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(vJamp_ - (vNormal_ / 60)));
   //         //�ǂ�ǂ�W�����v�x�N�g�������������Ă���
   //         vJamp_ = vJamp_ - (vNormal_ / 60);
   //     }
   // }
   // //�����W�����v�����Ă��Ȃ���triggerR�������Ă�����
   // if (Input::GetPadTrrigerR() && !isFly_ && !isRotation_) ARGUMENT_INITIALIZE(isRotation_, true);
   // //��]Flag��True1�Ȃ玩�M����]������
   // if (isJampRotation_)
   // {
   //     //�G�t�F�N�g�̕\��
   //     RotationEffect();
   //     angle_ += 0.5;
   //     //360�܂ōs������0�ɖ߂�
   //     if (angle_ >= TWOPI_DEGREES)
   //         angle_ = ZEROPI_DEGREES;
   // }
   // //������]Flag��True�Ȃ玩�g����]������
   // if (isRotation_)
   // {
   //     //�G�t�F�N�g�̕\��
   //     RotationEffect();
   //     //��]������
   //     angle_ += 1 - (rotationCount_ * 0.015f);
   //     //������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
   //     if (rotationCount_ >= 60)
   //     {
   //         //��]��~
   //         isRotation_ = false;
   //         rotationCount_ = 0;
   //     
   //     //rotationCount1�����₷
   //     rotationCount_++;
   // }

    //���̏�Ԃ̓���
    pState_->Update3D();

    //B����������J�����̈ʒu�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        //�J�����̏�ԕύX
        camStatus_ = (camStatus_ == LONG) ? SHORT
                                          : LONG;
    }

    //���V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) camAngle_ += 0.5f;
    
    //�E�V�����_�[����������p�x�ύX
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) camAngle_ -= 0.5f;

    //�E�X�e�B�b�N�ŃJ�����̊p�x������
    if (Input::GetPadStickR().x) camAngle_ += 0.03f * Input::GetPadStickR().x;
}

//�v���C���[����(2D�p)
void Player::MovingOperation2D(RayCastData* data)
{
    //���̏�Ԃ̓���
    pState_->Update2D();
}

//��]�G�t�F�N�g
void Player::RotationEffect()
{
    XMFLOAT3 Right = Model::GetBonePosition(hModel_, "Right2");//�E
    XMFLOAT3 Left = Model::GetBonePosition(hModel_, "Left2"); //��

    EmitterData data;
    data.textureFileName = "Cloud.png";
    data.position = Right;
    data.positionErr = XMFLOAT3(0.3, 0.2, 0.3);
    data.delay = 0;
    data.number = 5;
    data.lifeTime = 50;
    data.speed = 0.04f;
    data.speedErr = 0.8;
    data.size = XMFLOAT2(0.6, 0.6);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.00, 1.00);
    data.color = XMFLOAT4(0, 1, 1, 1);
    data.deltaColor = XMFLOAT4(0, -0.1, 0, -0.1);
    pParticle_->Start(data);


    data.position = Left;
    pParticle_->Start(data);
}

//�����G�t�F�N�g
void Player::FallEffect()
{
    EmitterData data;
    data.textureFileName = "Cloud.png";
    data.position = transform_.position_;
    data.position.y -= 4;
    data.delay = 0;
    data.number = 180;
    data.lifeTime = 50;
    data.dir = XMFLOAT3(0, 0, 1);
    data.dirErr = XMFLOAT3(0, 360, 0);
    data.speed = 0.2f;
    data.speedErr = 0.45;
    data.size = XMFLOAT2(1, 1);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.05, 1.05);
    data.color = XMFLOAT4(1, 1, 1, 0.2);
    data.deltaColor = XMFLOAT4(0, 0, 0, -0.004);
    pParticle_->Start(data);
}

//���C(3D�p)
void Player::StageRayCast(RayCastData* data)
{

    //�E
    data[Right].start = transform_.position_;        //���C�̔��ˈʒu
    XMVECTOR moveX = { 1,0,0 };                      //�������l
    moveX = XMVector3TransformCoord(moveX, transform_.mmRotate_);
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::BlockRayCast(hGroundModel_, &data[Right]);     //���C�𔭎�

    //��
    data[Left].start = transform_.position_;         //���C�̔��ˈʒu
    XMVECTOR moveX2 = { -1,0,0 };                    //�������l
    moveX2 = XMVector3TransformCoord(moveX2, transform_.mmRotate_);
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::BlockRayCast(hGroundModel_, &data[Left]);      //���C�𔭎�

    //�O
    data[Straight].start = transform_.position_;     //���C�̔��ˈʒu
    XMVECTOR moveZ = { 0,0,1 };                      //�������l
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::BlockRayCast(hGroundModel_, &data[Straight]);  //���C�𔭎�s

    //��
    data[Top].start = transform_.position_;         //���C�̔��ˈʒu]
    XMVECTOR moveY = { 0,1,0 };                    //�������l
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::BlockRayCast(hGroundModel_,&data[Top]);      //���C�𔭎�

    //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu]
    XMStoreFloat3(&data[Under].dir, down_);
    Model::BlockRayCast(hGroundModel_, &data[Under]);      //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 1)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 1)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }
    if (data[Straight].dist <= 1)
    {
        XMVECTOR dis = { 0,0,data[Straight].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp_ = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 0.9)//3
    {
        XMFLOAT3 moveL;

        if (isJamp_)
        {
            XMStoreFloat3(&moveL, (-vNormal_) / 10 * acceleration_);
        }
        else
        {
            XMStoreFloat3(&moveL, (-vNormal_) / 20 * acceleration_);
        }

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};

        acceleration_ += 0.03;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerState::state_ != PlayerState::rotationning_)
        {
            //��ԕύX
            PlayerState::state_ = PlayerState::standing_;
            PlayerState::state_->Enter();
        }
        acceleration_ = 1;
    }
}

//���C(2D�p)
void Player::StageRayCast2D()
{
    //�u���b�N�Ƃ̓����蔻������邽�߂Ƀg�����X�t�H�[����ۑ�
    XMFLOAT3 Colpos = transform_.position_;
    Colpos.x -= 0.5;

    //�E
    if (pstage_->IsBlock(&Colpos,0))
    {
        transform_.position_ = Colpos;
    }

    Colpos = transform_.position_;
    Colpos.x += 0.5;

    //��
    if (pstage_->IsBlock(&Colpos,1))
    {
        transform_.position_ = Colpos;
    }

    Colpos = transform_.position_;
    Colpos.y -= 1;

    //��
    if (pstage_->IsBlock(&Colpos,2))
    {
        transform_.position_ = Colpos;
        
        //��]����Ȃ��Ȃ�
        if (PlayerState::state_ != PlayerState::rotationning_)
        {
            //��ԕύX
            PlayerState::state_ = PlayerState::standing_;
            PlayerState::state_->Enter();
        }

        isJamp_ = false;
        isFly_ = false;
        isJampRotation_ = false;
        acceleration_ = 1;
    }

    Colpos = transform_.position_;
    Colpos.y += 1;

    //��
    if (pstage_->IsBlock(&Colpos,3))
    {
        transform_.position_ = Colpos;

        //��ԕύX
        PlayerState::state_ = PlayerState::standing_;
        PlayerState::state_->Enter();

        isJamp_ = false;
        acceleration_ = 1;
    }

    RayCastData data[MAX_RAY_SIZE];

    //�E
    data[Right].start = transform_.position_;        //���C�̔��ˈʒu
    XMVECTOR moveX = { 1,0,0 };                      //�������l
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //���C�𔭎�

    //��
    data[Left].start = transform_.position_;         //���C�̔��ˈʒu
    XMVECTOR moveX2 = { -1,0,0 };                    //�������l
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::RayCast(hGroundModel_, &data[Left]);      //���C�𔭎�

    //��
    data[Top].start = transform_.position_;         //���C�̔��ˈʒu]
    XMVECTOR moveY = { 0,1,0 };                    //�������l
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_, &data[Top]);      //���C�𔭎�

     //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, -vNormal_);//�������l
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 1)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 1)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp_ = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 0.9)//3
    {
        XMFLOAT3 moveL;
        XMVECTOR twoDUp = { 0,1,0,0 };

        XMStoreFloat3(&moveL, (-twoDUp) / 10 * acceleration_);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

        acceleration_ += 0.03;
    }
    else
    {
        //��]����Ȃ��Ȃ�
        if (PlayerState::state_ != PlayerState::rotationning_)
        {
            //��ԕύX
            PlayerState::state_ = PlayerState::standing_;
            PlayerState::state_->Enter();
        }

        isJamp_ = false;
        isFly_ = false;
        isJampRotation_ = false;
        acceleration_ = 1;
    }

}

//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
void Player::TimeMethod()
{
    Enter();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Warp")
    {
        isJamp_ = true;
        isJampRotation_ = false;
        isRotation_ = false;
        acceleration_ = 1;
    }
}

