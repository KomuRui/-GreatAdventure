#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1),

    ///////////////////�J����///////////////////////

    CAM_VEC(XMVectorSet(0.0f, 3.0f, -5.0f, 0.0f)),
    cameraPos_(transform_.rotate_.y)
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
}

//�X�V
void Player::Update()
{
    //�J�����̉�]
    cameraPos_ += Input::GetPadStickR().x * 3;

    //�v���C���[����
    MovingOperation();

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
    XMFLOAT3 camPos;
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(cameraPos_));
    XMMATRIX mRotateX4 = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
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

        float afterRotate = cameraPos_ + (atan2(Input::GetPadStickL().x, Input::GetPadStickL().y)) * 180.0 / 3.14159265;
        //transform_.rotate_.y = cameraPos_ + (atan2(Input::GetPadStickL().x, Input::GetPadStickL().y)) * 180.0 / 3.14159265;

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
            XMStoreFloat3(&move, (distance / 5));

            transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };
        }
    }

}

void Player::FaceOrientationSlowly(float afterRotate,bool &flag)
{
    if (transform_.rotate_.y < afterRotate)
        transform_.rotate_.y += fabs(afterRotate - transform_.rotate_.y) / 30;
    else
        transform_.rotate_.y -= fabs(afterRotate - transform_.rotate_.y) / 30;

    if (fabs(afterRotate - transform_.rotate_.y) <= 70)
    {
        flag = false;
    }
}
