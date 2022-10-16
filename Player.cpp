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
    JampRotationPreviousAngle(0),

    ///////////////////�J����///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 6.0f, -6.0f, 0.0f)),
    cameraPos_(transform_.rotate_.x,transform_.rotate_.y, transform_.rotate_.z),
    CamMat(XMMatrixIdentity())
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

	///////////////transform///////////////////

	transform_.position_.y = 33;
    //transform_.position_.y = 3;

    ///////////////Stage�̊e�f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = (Stage*)FindObject("Stage");
    hGroundModel_ = pstage_->GethModel();

    //�X�e�[�W��Position�擾
    StagePotision = pstage_->GetPosition();

    ///////////////���ƂȂ��x�N�g���̏�����///////////////////

    Up = { 0, 1, 0, 0 };

    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

}

//�X�V
void Player::Update()
{
    #pragma region Player�̉��Ƀ��C��ł��Ă����̖@�������߂�

    //RayCastData dataNormal;
    //dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
    //XMFLOAT3 moveY2;
    //XMStoreFloat3(&moveY2, -vNormal);//�������l
    //dataNormal.dir = moveY2;
    //Model::RayCast(hGroundModel_, &dataNormal);      //���C�𔭎�

    //XMVECTOR vdataNormal = XMLoadFloat3(&dataNormal.normal);

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

    //�v���C���[����
    MovingOperation();

    //Player���X�e�[�W�ɍ��킹�ĉ�]
    RotationInStage();

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

//�X�V�̑O�Ɉ��Ă΂��֐�
void Player::StartUpdate()
{
}

/////////////////////�֐�//////////////////////

//�J�����̏���
void Player::CameraBehavior()
{
    XMFLOAT3 camPos;                                         //�ŏI�I�ȃJ�����̈ʒu������ϐ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_��Vector�^
    XMVECTOR vCam = CAM_VEC;                                 //Player����J�����̃x�N�g�����쐬
    vCam = XMVector3TransformCoord(vCam, CamMat);            //vCam����

    vPos += vCam;                    //Player��Pos��Player����J�����̃x�N�g��������
    XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

    //�J�����̏���������߂邽�߂�StagePotision�������ď�����̃x�N�g�����쐬
    XMFLOAT3 UpDirection = { camPos.x - StagePotision.x ,camPos.y - StagePotision.y , camPos.z - StagePotision.z };

    //�J�����̂��낢��ݒ�
    Camera::SetUpDirection(XMLoadFloat3(&UpDirection));
    Camera::SetPosition(camPos);
    Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z));

}

//�X�e�[�W�ɍ��킹��Player����]
void Player::RotationInStage()
{
    //�X�e�[�W���玩�L�����܂ł̃x�N�g�������߂�
    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    //���C�g�̕������X�e�[�W���玩�L�����܂ł̃x�N�g���̉������ɐݒ�
    Light::SetDirection(XMFLOAT4(-Normal.x, -Normal.y, -Normal.z, 0));

    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(Up, vNormal);

        //X�̃x�N�g���𔲂����
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(Up, vNormal);

    if (dotX != 0)
    {
        transform_.mmRotate_ = XMMatrixRotationAxis(cross, acos(dotX));
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

        if (JampRotationPreviousAngle)
            mPreviousAngle = XMMatrixRotationAxis(cross, acos(dotX)) * XMMatrixRotationAxis(vNormal, JampRotationPreviousAngle);

        CamMat = XMMatrixRotationAxis(cross, acos(dotX));
    }
    else
    {
        transform_.mmRotate_ = XMMatrixRotationAxis(vNormal, Angle);
    }
}

//�v���C���[����
void Player::MovingOperation()
{
    static float beforeRotate = 0;
    static bool  flag = false;

    XMVECTOR front = { 0, 0, 1, 0 };
    XMFLOAT3 moveL = {0,0,0};

    //�X�e�[�W���玩�L�����܂ł̃x�N�g�������߂�
    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    XMVECTOR moveY = vNormal/40;


    if(Input::GetPadStickL().x > 0 || Input::GetPadStickL().y > 0 || Input::GetPadStickL().x < 0 || Input::GetPadStickL().y < 0)
    {
        
        if (!isJampRotation)
        {
            beforeRotate = Angle;

            float afterRotate = atan2(Input::GetPadStickL().x, Input::GetPadStickL().y);

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
            JampRotationPreviousAngle = atan2(Input::GetPadStickL().x, Input::GetPadStickL().y);

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

            XMFLOAT3 moveL;
            front = front / 10;
            XMStoreFloat3(&moveL, front);

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) && !isJamp)
    {
            vJamp = (vNormal)/2;

            isJamp = true;
    }

    if (isJamp)
    {
        if (XMVectorGetY(vJamp) >= 0)
        {
            XMStoreFloat3(&moveL, vJamp - moveY);
            vJamp = vJamp - moveY;

            transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
        }
    }

    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) && !isJampRotation && isJamp)
    {
        vJamp += (vNormal) / 2;
        isJampRotation = true;
    }

    if (isJampRotation)
    {
        Angle += 0.5;
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

//���C
void Player::StageRayCast()
{
    RayCastData data[MAX_RAY_SIZE];                  //���C�̌����쐬

    //�E
    data[Right].start = transform_.position_;        //���C�̔��ˈʒu
    XMFLOAT3 moveX = { 1,0,0 };                      //�������l
    data[Right].dir = moveX;
    Model::RayCast(hGroundModel_, &data[Right]);     //���C�𔭎�

    //��
    data[Left].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveX2 = { -1,0,0 };                    //�������l
    data[Left].dir = moveX2;
    Model::RayCast(hGroundModel_, &data[Left]);      //���C�𔭎�

    //�O
    data[Straight].start = transform_.position_;     //���C�̔��ˈʒu
    XMFLOAT3 moveZ = { 0,0,1 };                      //�������l
    data[Straight].dir = moveZ;
    Model::RayCast(hGroundModel_, &data[Straight]);  //���C�𔭎�s

    //��
    data[Back].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveZ2 = { 0,0,-1 };                    //�������l
    data[Back].dir = moveZ2;
    Model::RayCast(hGroundModel_, &data[Back]);      //���C�𔭎�

    //��
    data[Top].start = transform_.position_;          //���C�̔��ˈʒu
    XMFLOAT3 moveY = { 0,1,0 };                      //�������l
    data[Top].dir = moveY;
    Model::RayCast(hGroundModel_, &data[Top]);       //���C�𔭎�

    XMFLOAT3 Normal = { transform_.position_.x - StagePotision.x ,transform_.position_.y - StagePotision.y , transform_.position_.z - StagePotision.z };
    XMVECTOR vNormal = XMLoadFloat3(&Normal);
    vNormal = XMVector3Normalize(vNormal);

    //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;   
    XMStoreFloat3(&moveY2, -vNormal);//�������l
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    if (data[Right].dist <= 1)
    {
        transform_.position_.x -= 1 - data[Right].dist;
    }
    if (data[Left].dist <= 1)
    {
        transform_.position_.x += 1 - data[Left].dist;
    }
    if (data[Straight].dist <= 1)
    {
        transform_.position_.z -= 1 - data[Straight].dist;
    }
    if (data[Back].dist <= 1)
    {
        transform_.position_.z += 1 - data[Back].dist;
    }
    if (data[Top].dist <= 1)
    {
        transform_.position_.y -= 1 - data[Top].dist;
    }
    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        if (isJamp)
        {
            vNormal = (-vNormal) / 10;
            XMStoreFloat3(&moveL, vNormal);
        }
        else
        {
            vNormal = (-vNormal) / 40;
            XMStoreFloat3(&moveL, vNormal);
        }

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z};
       // transform_.position_.y += (0.8 - data[Under].dist) / 5;
    }
    else
    {
        isJamp = false;
        isJampRotation = false;
    }
}
