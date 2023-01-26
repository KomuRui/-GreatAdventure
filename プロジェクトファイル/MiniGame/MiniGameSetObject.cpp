#include "MiniGameSetObject.h"
#include "../Engine/Fbx.h"
#include "../Engine/Model.h"
#include "../Gimmick/Coin.h"
#include "../Enemy/PigEnemy.h"
#include "../Block/NormalBlock.h"
#include "../Block/BrickBlock.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Engine/Time.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
    static const float RADIUS_SMALL_VALUE = 3.0;  //���a�������������������鎞�̒l
    static const int   Z_DISTANCE = 200;          //PlayerZ�̈ʒu���玩�gZ�܂ł̋���
    static const int   MIN_GENERATION_SPEED = 30; //�ŏ������X�s�[�h(FPS)
    static const int   MAX_GENERATION_SPEED = 60; //�ő吶���X�s�[�h(FPS)
    static const int   MAX_GENERATION_TIME  = 26; //�ő吶������
    static const int   MIN_ANGLE = 0;             //�ŏ��p�x
    static const int   MAX_ANGLE = 360;           //�ő�p�x
    static const int   MIN_GENERATING_TYPE = 1;   //�ő吶���̎��
    static const int   MAX_GENERATING_TYPE = 3;   //�ŏ������̎��
    static const int   PIGENEMY_Z_POS_DIFF = 8;   //�ؕ�G�𐶐�����Ƃ���Z�ʒu�̈Ⴂ


    /// <summary>
    /// �֐��̃|�C���^�z��
    /// </summary>
    static void (MiniGameSetObject::* InstantiateArray[])() = { MiniGameSetObject::Center, MiniGameSetObject::Edge, MiniGameSetObject::MultipleEdge };

}

//�R���X�g���N�^
MiniGameSetObject::MiniGameSetObject(GameObject* parent)
    :GameObject(parent, "MiniGameSetObject"), radius_(ZERO), generatingSpeed_(ZERO), fpsCount_(ZERO)
{
}

//������
void MiniGameSetObject::Initialize()
{
    ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

    
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void MiniGameSetObject::StartUpdate()
{
    //���g��transform������
    ARGUMENT_INITIALIZE(transform_.position_, GameManager::GetpStage()->GetPosition());
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);

    //���C���΂��Ĕ��a��ݒ肷��
    RayCastData dataNormal;
    ARGUMENT_INITIALIZE(dataNormal.start, transform_.position_);
    ARGUMENT_INITIALIZE(dataNormal.dir, VectorToFloat3(DOWN_VECTOR));
    Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

    //�����𔼌a��(���߂�������菭����������������)
    ARGUMENT_INITIALIZE(radius_, dataNormal.dist - RADIUS_SMALL_VALUE);
}

//�X�V
void MiniGameSetObject::Update()
{
    //Player�����Ȃ���΂��̐揈�����Ȃ�
    if (GameManager::GetpPlayer() == nullptr) return;

    //�~�j�Q�[�����X�^�[�g���Ă��邩��Player������ł��Ȃ��̂Ȃ�I�u�W�F�N�g����
    if (MiniGameManager::IsPlay() && !GameManager::GetpPlayer()->isDie() && Time::GetTimef() < MAX_GENERATION_TIME)
        ObjectGeneration();

    //Z�̈ʒu�X�V
    ARGUMENT_INITIALIZE(transform_.position_.z, GameManager::GetpPlayer()->GetPosition().z + Z_DISTANCE);
}

//�`��
void MiniGameSetObject::Draw()
{
}

//���
void MiniGameSetObject::Release()
{
}

//�I�u�W�F�N�g����
void MiniGameSetObject::ObjectGeneration()
{
    //���������̃^�C�~���O�������Ȃ�
    if (generatingSpeed_ <= fpsCount_)
    {
        //����
        Generation();

        //���̐����X�s�[�h�ݒ�
        ARGUMENT_INITIALIZE(generatingSpeed_, Random(MIN_GENERATION_SPEED, MAX_GENERATION_SPEED));

        //�J�E���g������
        ARGUMENT_INITIALIZE(fpsCount_, ZERO);
    }

    //�J�E���g���₷
    fpsCount_++;
}

//����
void MiniGameSetObject::Generation()
{
    //�����ɂ���ČĂԊ֐��𕪂���
    (this->*InstantiateArray[Random(MIN_GENERATING_TYPE, MAX_GENERATING_TYPE)])();
}

//�^��
void MiniGameSetObject::Center() { Instantiate_Center<BrickBlock>(transform_.position_); }

//�[�ɕ�����
void MiniGameSetObject::MultipleEdge() {

    //��]�s��쐬
    XMMATRIX m = XMMatrixRotationZ(XMConvertToRadians(Random(MIN_ANGLE, MAX_ANGLE)));

    //�x�N�g������
    XMVECTOR v = XMVector3Normalize(XMVector3TransformCoord(DOWN_VECTOR, m)) * radius_;

    //�I�u�W�F�N�g�̈ʒu�����߂�
    XMFLOAT3 pos = Float3Add(transform_.position_, VectorToFloat3(v));

    Instantiate_Multiple_Edge<PigEnemy>(pos); 
}

//�[
void MiniGameSetObject::Edge(){

    //��]�s��쐬
    XMMATRIX m = XMMatrixRotationZ(XMConvertToRadians(Random(MIN_ANGLE, MAX_ANGLE)));

    //�x�N�g������
    XMVECTOR v = XMVector3Normalize(XMVector3TransformCoord(DOWN_VECTOR, m)) * radius_;

    //�I�u�W�F�N�g�̈ʒu�����߂�
    XMFLOAT3 pos = Float3Add(transform_.position_, VectorToFloat3(v));


    (Random(1, 2) == 1) ? Instantiate_Edge<Coin>(pos)
                        : Instantiate_Edge<NormalBlock>(pos);
}

//�g�̐^�񒆂ɐ���
template <class T>
void MiniGameSetObject::Instantiate_Center(XMFLOAT3 pos)
{
    T* p = Instantiate<T>(GetParent());
    p->SetPosition(pos);
}

//�g�̒[�ɐ���
template <class T>
void MiniGameSetObject::Instantiate_Edge(XMFLOAT3 pos)
{
    T* p = Instantiate<T>(GetParent());
    p->SetPosition(pos);
}

//�g�̒[�ɕ����̐���
template <class T>
void MiniGameSetObject::Instantiate_Multiple_Edge(XMFLOAT3 pos)
{
    //���̏o�����邩
    int r = Random(1, 3);

    //r�̕��o��������
    for (int i = 0; i < r; i++)
    {
        pos.z += i * PIGENEMY_Z_POS_DIFF;
        T* p = Instantiate<T>(GetParent());
        p->SetPosition(pos);
    }
}




