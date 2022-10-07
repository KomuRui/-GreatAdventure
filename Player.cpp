#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), hGroundModel_(0),

    ///////////////////�J����///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f)),
    cameraPos_(transform_.rotate_.x,transform_.rotate_.y, transform_.rotate_.z)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Player::Initialize()
{

	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Star_Main_Character.fbx");
	assert(hModel_ >= 0);

	///////////////transform///////////////////

	transform_.position_.y = 33;

  /*  transform_.rotate_.x = 1;
    transform_.rotate_.y = 1;
    transform_.rotate_.z = 1;*/

    pstage_ = (Stage*)FindObject("Stage");
    hGroundModel_ = pstage_->GethModel();

    Up = { 0, 1, 0, 0 };
}

//�X�V
void Player::Update()
{
    XMVECTOR front = { 0, 0, 1, 0 };


    XMMATRIX mRotaX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotaY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotaZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

    if (Input::IsKey(DIK_A))
    {
        XMVECTOR Left = { 0,-3,0,0 };
        XMFLOAT3 moveL;
        XMStoreFloat3(&moveL, Left);

        transform_.rotate_ = { transform_.rotate_.x + moveL.x, transform_.rotate_.y + moveL.y, transform_.rotate_.z + moveL.z };
    }
    if (Input::IsKey(DIK_D))
    {
        XMVECTOR Left = { 0,3,0,0 };
        XMFLOAT3 moveL;
        XMStoreFloat3(&moveL, Left);

        transform_.rotate_ = { transform_.rotate_.x + moveL.x, transform_.rotate_.y + moveL.y, transform_.rotate_.z + moveL.z };
    }
    if (Input::IsKey(DIK_W))
    {
        front = XMVector3TransformCoord(front, mRotaX);//vCam����
        front = XMVector3TransformCoord(front, mRotaY);//vCam����
        front = XMVector3TransformCoord(front, mRotaZ);//vCam����

        XMFLOAT3 moveL;
        front = front / 10;
        XMStoreFloat3(&moveL, front);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }


    RayCastData Down;
    Down.start = transform_.position_;        //���C�̔��ˈʒu
    XMFLOAT3 moveX = { 0,-1,0 };              //�������l
    Down.dir = moveX;
    Model::RayCast(hGroundModel_, &Down);     //���C�𔭎�

    if (Down.hit)
    {
        XMVECTOR normal = XMLoadFloat3(&Down.normal);

        //Up = XMVector3TransformCoord(Up, mRotaX);//vCam����
        //Up = XMVector3TransformCoord(Up, mRotaY);//vCam����
        //Up = XMVector3TransformCoord(Up, mRotaZ);//vCam����

        //transform_.rotate_ = { transform_.rotate_.x + angle ,transform_.rotate_.y , transform_.rotate_.z };

        if (transform_.rotate_.x > 360 || transform_.rotate_.y > 360 || transform_.rotate_.z > 360)
        {
            if (transform_.rotate_.x > 360)
                transform_.rotate_.x -= 360;

            if (transform_.rotate_.y > 360)
                transform_.rotate_.y -= 360;

            if (transform_.rotate_.z > 360)
                transform_.rotate_.z -= 360;
        }

            Up = normal;
       

    }

    //�J�����̉�]
    cameraPos_.y += Input::GetPadStickR().x * 3;
    cameraPos_.x += Input::GetPadStickR().y;

    //�v���C���[����
    MovingOperation();

    //�J�����̋���
    CameraBehavior();

    //�X�e�[�W�Ƃ̓����蔻��
    StageRayCast();
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
    XMFLOAT3 camPos;
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(cameraPos_.y));
    XMMATRIX mRotateX4 = XMMatrixRotationX(XMConvertToRadians(cameraPos_.x));
    XMMATRIX mRotateZ1 = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
    XMVECTOR vCam = CAM_VEC;
    vCam = XMVector3TransformCoord(vCam, mRotateZ1);//vCam����
    vCam = XMVector3TransformCoord(vCam, mRotateX4);//vCam����
    vCam = XMVector3TransformCoord(vCam, mRotateY);//vCam����

    vPos += vCam;
    XMStoreFloat3(&camPos, vPos);

    Camera::SetPosition(camPos);
    Camera::SetTarget(XMFLOAT3(transform_.position_.x, transform_.position_.y + 1, transform_.position_.z));
}

//�v���C���[����
void Player::MovingOperation()
{
    XMFLOAT3     cam = { Camera::GetPosition().x,transform_.position_.y,Camera::GetPosition().z };
    XMVECTOR     vCam = XMLoadFloat3(&cam);
    XMVECTOR     vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR     distance = XMVector3Normalize(vPos - vCam);
    static float beforeRotate = 0;
    static bool  flag = false;

    if(Input::GetPadStickL().x > 0 || Input::GetPadStickL().y > 0 || Input::GetPadStickL().x < 0 || Input::GetPadStickL().y < 0)
    {
        beforeRotate = transform_.rotate_.y;

        XMMATRIX mRotate90 = XMMatrixRotationY(atan2(Input::GetPadStickL().x , Input::GetPadStickL().y));
        distance = XMVector3TransformCoord(distance, mRotate90);

        float afterRotate = cameraPos_.y + (atan2(Input::GetPadStickL().x, Input::GetPadStickL().y)) * 180.0 / 3.14159265;

        if (beforeRotate != afterRotate)
        {
            flag = true;
            FaceOrientationSlowly(afterRotate, flag);
        }
        else
            transform_.rotate_.y = afterRotate;

        if (!flag)
        {
            XMFLOAT3 move;
            if (fabs(Input::GetPadStickL().x) != 0 && fabs(Input::GetPadStickL().y) != 0)
            {
                float avg = (fabs(Input::GetPadStickL().x) + fabs(Input::GetPadStickL().y));

                if (avg > 1)
                {
                    avg = 1;
                }
                XMStoreFloat3(&move, ((distance / 10) * avg));
            }
            else if(fabs(Input::GetPadStickL().x) != 0)
            {
                XMStoreFloat3(&move, ((distance / 10) * fabs(Input::GetPadStickL().x)));
            }
            else
            {
                XMStoreFloat3(&move, ((distance / 10) * fabs(Input::GetPadStickL().y)));
            }

            transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };
        }
    }

}

//�������Ǝ��̊p�x�Ɍ���
void Player::FaceOrientationSlowly(float afterRotate,bool &flag)
{
    if (afterRotate < 0)
        afterRotate += 360;

    if (transform_.rotate_.y < afterRotate)
        transform_.rotate_.y += fabs(afterRotate - transform_.rotate_.y) / 10;
    else
        transform_.rotate_.y -= fabs(afterRotate - transform_.rotate_.y) / 10;

    if (fabs(afterRotate - transform_.rotate_.y) <= 60)
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

    //��
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2 = { 0,-1,0 };                     //�������l
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    if (data[Right].dist <= 0.5)
    {
        transform_.position_.x -= 0.5 - data[Right].dist;
    }
    if (data[Left].dist <= 0.5)
    {
        transform_.position_.x += 0.5 - data[Left].dist;
    }
    if (data[Straight].dist <= 0.5)
    {
        transform_.position_.z -= 0.5 - data[Straight].dist;
    }
    if (data[Back].dist <= 0.5)
    {
        transform_.position_.z += 0.5 - data[Back].dist;
    }
    if (data[Top].dist <= 0.5)
    {
        transform_.position_.y -= 0.5 - data[Top].dist;
    }
    if (data[Under].dist <= 3)
    {
        transform_.position_.y += (0.8 - data[Under].dist) / 5;
    }
}
