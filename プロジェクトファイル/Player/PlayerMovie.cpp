#include "PlayerMovie.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"

//�R���X�g���N�^
PlayerMovie::PlayerMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "Star_Main_Character.fbx", "Player"), vMovieCam_(XMVectorSet(-4, 6, 2, ZERO))
{
}

//������
void PlayerMovie::ChildInitialize()
{
}

//�X�V
void PlayerMovie::ChildUpdate()
{
    //�J����
    CameraBehavior();
}

//�J�����̏���
void PlayerMovie::CameraBehavior()
{

    XMFLOAT3 camPos;                                         //�ŏI�I�ȃJ�����̈ʒu������ϐ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);     //transform_.position_��Vector�^
    XMVECTOR vCam_ = vMovieCam_;                             //Player����J�����̃x�N�g�����쐬
    vCam_ = XMVector3TransformCoord(vCam_, totalMx_);        //vCam����

    vPos += vCam_;                   //Player��Pos��Player����J�����̃x�N�g��������
    XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

    XMFLOAT3 camTar = Float3Add(transform_.position_, XMFLOAT3(ZERO, ZERO, -4));

    //�J�����̂��낢��ݒ�
    Camera::SetUpDirection(vNormal_);
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTar);

    //���C�g�̈ʒu�ݒ�
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, vNormal_ + XMLoadFloat3(&transform_.position_));
    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}
