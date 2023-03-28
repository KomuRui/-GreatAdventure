#include "PlayerMovie.h"
#include "../Engine/GameObject/Camera.h"
#include "../Engine/GameObject/Light.h"
#include "../Engine/ResourceManager/Time.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../Gimmick/Movie/MovieCoin.h"
#include "../Enemy/BossEnemyMovie.h"
#include "../Engine/ResourceManager/VFX.h"

//�R���X�g���N�^
PlayerMovie::PlayerMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "MainCharacter/Star_Main_Character.fbx", "Player"), vMovieCam_(XMVectorSet(-4, 6, 2, ZERO)), hTime_((int)ZERO)
{
}

//�f�X�g���N�^
PlayerMovie::~PlayerMovie()
{
    //���
    VFX::Release();
}

//������
void PlayerMovie::ChildInitialize()
{
    //�^�C�}�[��ǉ�
    ARGUMENT_INITIALIZE(hTime_, Time::Add());

    //�{�X�ւ̕��������߂ċz�������G�t�F�N�g�\��
    XMFLOAT3 pBossPos = ((BossEnemyMovie*)FindObject("BossEnemyMovie"))->GetPosition();
    XMVECTOR dir = (XMLoadFloat3(&pBossPos) - XMLoadFloat3(&transform_.position_)) + UP_VECTOR * 2;
    PlayerEffectManager::AbsorptionEffect(transform_.position_, dir,vNormal_);
}

//�X�V
void PlayerMovie::ChildUpdate()
{
    //�R�C�����o
    CoinRelease();

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

//�R�C�����o
void PlayerMovie::CoinRelease()
{
    //�����^�C�}�[�����b�N���Ă���Ȃ�A�����b�N
    if (Time::isLock(hTime_))Time::UnLock(hTime_);

    //�����R�C����1���ł����邩��0.5�b�����Ă����
    if (CoinManager::GetCoinNum() > ZERO && Time::GetTimef(hTime_) > 0.25f)
    {
        //�R�C���\��
        Instantiate<MovieCoin>(GetParent());

        //���Z�b�g
        Time::Reset(hTime_);

        //�R�C������
        CoinManager::DecrementCoin(1);
    }
}