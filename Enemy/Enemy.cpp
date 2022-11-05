#include "Enemy.h"
#include "../Engine/Model.h"

Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name), hGroundModel_(0), Angle(0), acceleration(1), aiState_(MOVE), operationTime_(0),

    TotalMx(XMMatrixIdentity()),
    vNormal(XMVectorSet(0, -1, 0, 0)),
    moveDir_(XMVectorSet(0, 0, 1, 0))
{
}

//������
void Enemy::ChildInitialize()
{
	///////////////���ƂȂ��x�N�g���̏�����///////////////////

	Up = { 0, 1, 0, 0 };
	Down = { 0, -1, 0, 0 };

	///////////////���X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

	transform_.mFlag_ = true;
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Enemy::ChildStartUpdate()
{
    ///////////////Stage�̊e�f�[�^�擾///////////////////

    //���f���ԍ��擾
    pstage_ = (TutorialStage*)FindObject("TutorialStage");
    hGroundModel_ = pstage_->GethModel();

    ///////////////transform///////////////////

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//�������l
    dataNormal.dir = moveY2;
    Model::AllRayCast(hModel_, &dataNormal);      //���C�𔭎�

    vNormal = XMLoadFloat3(&dataNormal.normal);
}

//�X�V
void Enemy::UpdateMove()
{
#pragma region �L�����̉��Ƀ��C��ł��Ă����̖@�������߂�

    RayCastData dataNormal;
    dataNormal.start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//�������l
    dataNormal.dir = moveY2;
    Model::RayCast(hGroundModel_, &dataNormal);      //���C�𔭎�(All)

    if (dataNormal.hit && (XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&dataNormal.normal)))))
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

    //Player���X�e�[�W�ɍ��킹�ĉ�]
    RotationInStage();

    //�X�e�[�W�Ƃ̓����蔻��
    StageRayCast();

    //�L�����̓���
    MovingOperation();
}

//�`��
void Enemy::ChildDraw()
{
}

//�X�e�[�W�ɍ��킹��Player����]
void Enemy::RotationInStage()
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

        }
        else
        {
            transform_.mmRotate_ = TotalMx;

            XMStoreFloat4x4(_Out_ & crs, _In_ XMMatrixRotationAxis(vNormal, Angle));
            transform_.mmRotate_ *= transform_.QuaternionToMattrix(make_quaternion_from_rotation_matrix(crs));

        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        Up = vNormal;
    }
}

//���C(�~�p)
void Enemy::StageRayCast()
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
    Model::RayCast(hGroundModel_, &data[Top]);      //���C�𔭎�

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
        XMVECTOR dis = { 0,data[Top].dist,0 };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveY - dis));
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        XMStoreFloat3(&moveL, (-vNormal) / 10);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

}

//�L�����̓���
void Enemy::MovingOperation()
{
    //��Ԃɂ����Enemy�̍s����ω�������
    switch (aiState_)
    {
    //�ҋ@
    case WAIT:

        //WAIT���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
        if (operationTime_ == 0)
            operationTime_ = (rand() % 13 + 6) * 10;

        Wait();
        break;
    //�ړ�
    case MOVE:

        //MOVE���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
        if (operationTime_ == 0)
            operationTime_ = (rand() % 19 + 12) * 10;

        Move();
        break;
    //��]
    case ROTATION:
        Rotation();
        break;
    //�ǂ�ł��Ȃ���
    default:
        aiState_ = WAIT;
        operationTime_ = 0;
        break;
    }

    //���̏�Ԃɕς��܂ł̎��Ԃ�i�߂�
    operationTime_++;
}


///////////////////AI�s���֐�////////////////////

//�ҋ@
void Enemy::Wait()
{
}

//�s��
void Enemy::Move()
{
    //XMFLOAT3�^��1Fream�����ʂ��i�[����ϐ�
    XMFLOAT3 move;

    //�i�s�x�N�g�������g�̉�]�s��ŉ�]������move�Ɋi�[(1Fream�����ʂ�0.1�ɂ��Ă���)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(moveDir_, transform_.mmRotate_)) / 10);

    //���g��transform�ɉ��Z
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };
}

//��]
void Enemy::Rotation()
{
}
