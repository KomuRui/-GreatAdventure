#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), hGroundModel_(0), Angle(0), isJamp(false), vJamp(XMVectorSet(0, 0, 0, 0)), isJampRotation(false),
    JampRotationPreviousAngle(0), acceleration(1),

    ///////////////////�J����///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 25.0f, -30.0f, 0.0f)),
    CamMat(XMMatrixIdentity()),
    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0,-1,0,0))
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Player::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= 0);

    Model::SetAmbient(hModel_, 20);

    ///////////////���ƂȂ��x�N�g���̏�����///////////////////

    Up = { 0, 1, 0, 0 };
    Down = { 0, -1, 0, 0 };

    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Player::StartUpdate()
{
    ///////////////Stage�̊e�f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = (TutorialStage*)FindObject("TutorialStage");
    hGroundModel_ = pstage_->GethModel();

    ///////////////transform///////////////////

    transform_.position_ = pstage_->GetPos();

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//�������l
    dataNormal.dir = moveY2;
    Model::AllRayCast(hModel_ ,&dataNormal);      //���C�𔭎�

    vNormal = XMLoadFloat3(&dataNormal.normal);

    //�J�����̃|�W�V�������������Ă���
    //2D�̎�
    if (!pstage_->GetthreeDflag())
        NowCamPos = { transform_.position_.x, transform_.position_.y + 1, transform_.position_.z + 20 };
}


//�X�V
void Player::Update()
{
    #pragma region Player�̉��Ƀ��C��ł��Ă����̖@�������߂�

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//�������l
    dataNormal.dir = moveY2;
    Model::AllRayCast(hModel_, &dataNormal, "Stage/Tutorial/first_Stage.fbx");      //���C�𔭎�(All)

    if (dataNormal.hit && ( XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)))))
    {
        //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)), XMVector3Normalize(vNormal)));

        //�p�x��60�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
        if (acos(dotX) < XMConvertToRadians(60) && acos(dotX) > XMConvertToRadians(-60))
        {
            //������ƕ��
            vNormal = XMVector3Normalize((XMLoadFloat3(&dataNormal.normal) + vNormal) + vNormal * 30);
            Down = -vNormal;
        }

    }

#pragma endregion

    #pragma region �R���g���[���[���������Ɏg���L�[�{�[�h����

    if (Input::IsKey(DIK_A))
    {
        Angle -= 0.1;

        if (-360 >= Angle)
            Angle = 0;
    }

    if (Input::IsKey(DIK_D))
    {
        Angle += 0.1;

        if (360 <= Angle)
            Angle = 0;
    }


    if (Input::IsKey(DIK_W))
    {
        XMVECTOR front = { 0, 0, 1, 0 };

        front = XMVector3TransformCoord(front, transform_.mmRotate_);//vCam����

        XMFLOAT3 moveL;
        front = front / 10;
        XMStoreFloat3(&moveL, front);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

#pragma endregion

    if (!pstage_->GetthreeDflag())
        //�v���C���[����2D
        MovingOperation2D();
    else
        //�v���C���[����
        MovingOperation();

    //Player���X�e�[�W�ɍ��킹�ĉ�]
    RotationInStage();

    if (!pstage_->GetthreeDflag())
        //�X�e�[�W�Ƃ̓����蔻��2D
        StageRayCast2D();
    else
        //�X�e�[�W�Ƃ̓����蔻��
        StageRayCast();

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
    if (pstage_->GetthreeDflag())
    {
        XMFLOAT3 camPos;                                         //�ŏI�I�ȃJ�����̈ʒu������ϐ�
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_��Vector�^
        XMVECTOR vCam = CAM_VEC;                                 //Player����J�����̃x�N�g�����쐬
        vCam = XMVector3TransformCoord(vCam, CamMat);            //vCam����

        vPos += vCam;                    //Player��Pos��Player����J�����̃x�N�g��������
        XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

        //�J�����̏���������߂邽�߂�StagePotision�������ď�����̃x�N�g�����쐬
        XMFLOAT3 UpDirection = { XMVectorGetX(-vNormal), XMVectorGetY(-vNormal), XMVectorGetZ(-vNormal) };

        //�J�����̂��낢��ݒ�
        Camera::SetUpDirection(vNormal);
        Camera::SetPosition(camPos);
        Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z));

        Light::SetDirection(XMFLOAT4(XMVectorGetX(-vNormal), XMVectorGetY(-vNormal), XMVectorGetZ(-vNormal), 0));
    }
    else
    {
        //������J�����̃|�W�V�������Y��1��藣��Ă���Ȃ�
        if (fabs(transform_.position_.y - NowCamPos.y) > 0.5 && !isJamp)
        {
            XMFLOAT3 pos = { transform_.position_.x,transform_.position_.y,transform_.position_.z + 20 };
                
            XMStoreFloat3(&NowCamPos,XMVectorLerp(XMLoadFloat3(&NowCamPos), XMLoadFloat3(&pos), 0.05));
        }

        //�J�����̂��낢��ݒ�
        Camera::SetPosition(XMFLOAT3(transform_.position_.x, NowCamPos.y, NowCamPos.z));
        Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y + 1, transform_.position_.z));

        Light::SetDirection(XMFLOAT4(0 ,0, -1, 0));
    }
}

//�X�e�[�W�ɍ��킹��Player����]
void Player::RotationInStage()
{
    float4x4 crs;

    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(Up), XMVector3Normalize(vNormal));

        //X�̃x�N�g���𔲂����
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (!pstage_->GetthreeDflag())
    {
        XMVECTOR TwoDUp = { 0, 1, 0, 0 };

        TotalMx = XMMatrixIdentity();
        transform_.mmRotate_ = TotalMx;

        XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(TwoDUp, Angle));
        transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));

        if (isJampRotation)
            mPreviousAngle = (TotalMx * XMMatrixRotationAxis(TwoDUp, JampRotationPreviousAngle));
    }
    else
    {

        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {

            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(cross, acos(dotX)));
            TotalMx *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));
            transform_.mmRotate_ = TotalMx;


            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(vNormal, Angle));
            transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));


            if (isJampRotation)
                mPreviousAngle = (TotalMx * XMMatrixRotationAxis(cross, acos(dotX))) * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle);

            CamMat = TotalMx;
        }
        else
        {
            transform_.mmRotate_ = TotalMx;

            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(vNormal, Angle));
            transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));

            if (isJampRotation)
                mPreviousAngle = (TotalMx * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle));
        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        Up = vNormal;
    }
}

//�v���C���[����(�~�p)
void Player::MovingOperation()
{
    static float beforeRotate = 0;
    static bool  flag = false;

    XMVECTOR front = { 0, 0, 1, 0 };

    XMFLOAT3 moveL = { 0, 0, 0};

    XMVECTOR moveY = vNormal/40;

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if(PadLx > 0 || padLy > 0 || PadLx < 0 || padLy < 0)
    {

        if (!isJampRotation)
        {
            beforeRotate = Angle;

            float afterRotate = atan2(PadLx, padLy);

            /*if (beforeRotate != afterRotate)
            {
                flag = true;
                FaceOrientationSlowly(afterRotate, flag);
            }
            else*/
            Angle = afterRotate;

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = atan2(PadLx, padLy);

        if (!flag)
        {
            if (!isJampRotation)
            {
                front = XMVector3TransformCoord(front, transform_.mmRotate_);
            }
            else
            {
                front = XMVector3TransformCoord(front, mPreviousAngle);
            }

            front = front / 10;
            XMStoreFloat3(&moveL, front);

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //�����W�����v�����Ă��Ȃ���Ԃ�A�{�^�����������Ȃ�
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
        //�W�����v�̃x�N�g���ɒl����
        vJamp = (vNormal)/2;

        //�W�����v���Ă����Ԃɂ���
        isJamp = true;
    }

    //�����W�����v�����Ă�����
    if (isJamp)
    {
        //�W�����v����x�N�g�����v���X��������
        if (XMVectorGetY(vJamp) >= 0)
        {
            //�ǂ�ǂ�x�N�g�������������Ă���
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            //Transform�ɂ���
            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //�����W�����v�����Ă��ĉ�]�����Ă��Ȃ���B�������Ă�����
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        //�W�����v�̃x�N�g���ɂ���
        vJamp += (vNormal) / 2;

        //��]Flag��On�ɂ���
        isJampRotation = true;
    }

    //��]Flag��True1�Ȃ玩�M����]������
    if (isJampRotation)
    {
        Angle += 0.5;

        //360�܂ōs������0�ɖ߂�
        if (Angle >= 360)
            Angle = 0;
    }

}

//�v���C���[����(2D�p)
void Player::MovingOperation2D()
{
    XMVECTOR front = { 0, 0, -1, 0 };

    XMFLOAT3 moveL = { 0, 0, 0 };

    XMVECTOR moveY = { 0,1.0f / 60.0f,0,0 };

    float PadLx = Input::GetPadStickL().x;
    float padLy = Input::GetPadStickL().y;

    if (PadLx > 0 || PadLx < 0)
    {
        //padLy = 0;

        if (!isJampRotation)
        {
            Angle = -atan2(PadLx, -padLy);

            JampRotationPreviousAngle = Angle;
        }
        else
            JampRotationPreviousAngle = -atan2(PadLx, padLy);


        if (!isJampRotation)
        {
            front = XMVector3TransformCoord(front, transform_.mmRotate_);
        }
        else
        {
            front = XMVector3TransformCoord(front, mPreviousAngle);
        }

        front = front / 10;
        XMStoreFloat3(&moveL, -front);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z };

    }

    //�W�����v�����Ă��Ȃ��Ȃ�
    if (!isJamp)
    {
        RayCastData dataNormal;
        dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
        XMFLOAT3 moveY2 = { 0,-1,0};
        dataNormal.dir = moveY2;
        Model::AllRayCast(hModel_, &dataNormal, "Stage/Tutorial/first_Stage.fbx");      //���C�𔭎�(All)

        //��������������1.0f��菬�����Ȃ�
        if (dataNormal.dist < 1.0f)
        {
            dataNormal.pos.y += 1.0f;
            transform_.position_ = dataNormal.pos;
            acceleration = 1;
        }
    }

    //�����W�����v�����Ă��Ȃ���Ԃ�A�{�^�����������Ȃ�
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
        XMVECTOR TwoDUp = { 0,1,0,0 };

        //�W�����v�̃x�N�g���ɒl����
        vJamp = (TwoDUp) / 2;

        //�W�����v���Ă����Ԃɂ���
        isJamp = true;
    }

    //�����W�����v�����Ă�����
    if (isJamp)
    {
        //�W�����v����x�N�g�����v���X��������
        if (XMVectorGetY(vJamp) >= 0)
        {
            //�ǂ�ǂ�x�N�g�������������Ă���
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            //Transform�ɂ���
            transform_.position_ = { transform_.position_.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    //�����W�����v�����Ă��ĉ�]�����Ă��Ȃ���B�������Ă�����
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        XMVECTOR TwoDUp = { 0,1,0,0 };

        //�W�����v�̃x�N�g���ɂ���
        vJamp += (TwoDUp) / 2;

        //��]Flag��On�ɂ���
        isJampRotation = true;
    }

    //��]Flag��True1�Ȃ玩�M����]������
    if (isJampRotation)
    {
        Angle += 0.5;

        //360�܂ōs������0�ɖ߂�
        if (Angle >= 360)
            Angle = 0;
    }

}

//�������Ǝ��̊p�x�Ɍ���
void Player::FaceOrientationSlowly(float afterRotate,bool &flag)
{
    if (afterRotate < 0)
        afterRotate += XMConvertToRadians(360);

    if (Angle < afterRotate)
        Angle += fabs(afterRotate - Angle) / 10;
    else
        Angle -= fabs(afterRotate - Angle) / 10;

    if (fabs(afterRotate - Angle) <= XMConvertToRadians(60))
    {
        flag = false;
    }
}

//���C(�~�p)
void Player::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];                  //���C�̌����쐬

    //�E
    data[Right].start = transform_.position_;        //���C�̔��ˈʒu
    XMVECTOR moveX = { 1,0,0 };                      //�������l
    moveX = XMVector3TransformCoord(moveX, transform_.mmRotate_);
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::RayCast(hGroundModel_, &data[Right]);     //���C�𔭎�

    //��
    data[Left].start = transform_.position_;         //���C�̔��ˈʒu
    XMVECTOR moveX2 = { -1,0,0 };                    //�������l
    moveX2 = XMVector3TransformCoord(moveX2, transform_.mmRotate_);
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::RayCast(hGroundModel_, &data[Left]);      //���C�𔭎�

    //�O
    data[Straight].start = transform_.position_;     //���C�̔��ˈʒu
    XMVECTOR moveZ = { 0,0,1 };                      //�������l
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::RayCast(hGroundModel_, &data[Straight]);  //���C�𔭎�s

    //��
    data[Back].start = transform_.position_;         //���C�̔��ˈʒu
    XMVECTOR moveZ2 = { 0,0,-1 };                    //�������l
    moveZ2 = XMVector3TransformCoord(moveZ2, transform_.mmRotate_);
    XMStoreFloat3(&data[Back].dir, moveZ2);
    Model::RayCast(hGroundModel_, &data[Back]);      //���C�𔭎�

    //��
    data[Top].start = transform_.position_;         //���C�̔��ˈʒu]
    XMVECTOR moveY = { 0,1,0 };                    //�������l
    moveY = XMVector3TransformCoord(moveY, transform_.mmRotate_);
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::RayCast(hGroundModel_,&data[Top]);      //���C�𔭎�

    //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;   
    XMStoreFloat3(&moveY2, -vNormal);//�������l
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //���C�𔭎�

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
    if (data[Back].dist <= 1)
    {
        XMVECTOR dis = { 0,0,-data[Back].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        if (isJamp)
        {
            XMStoreFloat3(&moveL, (-vNormal) / 10);
        }
        else
        {
            XMStoreFloat3(&moveL, (-vNormal) / 20);
        }

        //XMStoreFloat3(&moveL, (-vNormal) / 10);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
    }
}

//���C(2D�p)
void Player::StageRayCast2D()
{
    RayCastData data[MAX_RAY_SIZE];                  //���C�̌����쐬

    //�E
    data[Right].start = transform_.position_;        //���C�̔��ˈʒu
    XMVECTOR moveX = { 0.5,0,0 };                      //�������l
    XMStoreFloat3(&data[Right].dir, moveX);
    Model::AllRayCast(hModel_, &data[Right], "Stage/Tutorial/first_Stage.fbx");     //���C�𔭎�

    //��
    data[Left].start = transform_.position_;         //���C�̔��ˈʒu
    XMVECTOR moveX2 = { -0.5,0,0 };                    //�������l
    XMStoreFloat3(&data[Left].dir, moveX2);
    Model::AllRayCast(hModel_, &data[Left], "Stage/Tutorial/first_Stage.fbx");      //���C�𔭎�

    //��
    data[Top].start = transform_.position_;         //���C�̔��ˈʒu]
    XMVECTOR moveY = { 0,1,0 };                    //�������l
    XMStoreFloat3(&data[Top].dir, moveY);
    Model::AllRayCast(hModel_, &data[Top], "Stage/Tutorial/first_Stage.fbx");      //���C�𔭎�

    //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, -vNormal);//�������l
    data[Under].dir = moveY2;
    Model::AllRayCast(hModel_, &data[Under], "Stage/Tutorial/first_Stage.fbx");      //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Right].dist <= 0.5)
    {
        XMVECTOR dis = { data[Right].dist,0,0 };
        //dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX - dis));
    }
    if (data[Left].dist <= 0.5)
    {
        XMVECTOR dis = { -data[Left].dist,0,0 };
        //dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveX2 - dis));
    }

    if (data[Top].dist <= 1)
    {
        isJamp = false;

        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 0.9)//3
    {
        XMFLOAT3 moveL;
        XMFLOAT3 beforPosition;
        XMVECTOR twoDUp = { 0,1,0,0 };

        XMStoreFloat3(&moveL, ((-twoDUp) / 10) * acceleration);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };

        acceleration += 0.03;
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
        acceleration = 1;
    }
}
