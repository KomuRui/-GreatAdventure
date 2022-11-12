#include "Enemy.h"
#include "../Engine/Model.h"

Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), aiState_(MOVE), operationTime_(0), hGroundModel_(-1), stateCount_(0),
    rotationAngle_(0), rotationTotal_(0), front_(XMVectorSet(0,0,1,0)), dotX_(0), rotationSign_(1)
{
}

//������
void Enemy::ChildInitialize()
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Enemy::ChildStartUpdate()
{
    ///////////////�����蔻��ݒ�///////////////////

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.3, 0), XMFLOAT3(2, 2.2, 2));
    AddCollider(collision);

    ///////////////Player�T��////////////////

    pPlayer_ = (Player*)FindObject("Player");

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    hGroundModel_ = pstage_->GethModel();

    ///////////////�A�j���[�V����///////////////////

    //�J�n
    Model::SetAnimFrame(hModel_, 1, 60, 3);
}

//�X�V
void Enemy::UpdateMove()
{
#pragma region �L�����̉��Ƀ��C��ł��Ă����̖@�������߂�

    RayCastData data[MAX_RAY_SIZE];                  //���C�̌����쐬
    data[Under].start = transform_.position_;         //���C�̔��ˈʒu
    XMFLOAT3 moveY2;
    XMStoreFloat3(&moveY2, Down);//�������l
    data[Under].dir = moveY2;
    Model::RayCast(hGroundModel_, &data[Under]);      //���C�𔭎�(All)

    if (data[Under].hit && (XMVectorGetX(vNormal) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetY(-vNormal) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data[Under].normal))) || XMVectorGetZ(-vNormal) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)))))
    {
        //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data[Under].normal)), XMVector3Normalize(vNormal)));

        //�p�x��60�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
        if (acos(dotX) < XMConvertToRadians(60) && acos(dotX) > XMConvertToRadians(-60))
        {
            //������ƕ��
            vNormal = XMVector3Normalize((XMLoadFloat3(&data[Under].normal) + vNormal) + vNormal * 30);
            Down = -vNormal;
        }

    }
#pragma endregion

    //Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
    PlayerNearWithIsCheck();

    //�L�����̓���
    MovingOperation(data);

    //Player���X�e�[�W�ɍ��킹�ĉ�]
    //RotationInStage();

    //�X�e�[�W�Ƃ̓����蔻��
    StageRayCast(data);
}

//�`��
void Enemy::ChildDraw()
{
}

//�X�e�[�W�ɍ��킹��Player����]
void Enemy::RotationInStage()
{
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

        transform_.mmRotate_ *= XMMatrixRotationAxis(TwoDUp, Angle);

    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            TotalMx *= XMMatrixRotationAxis(cross, acos(dotX));
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);
        }
        else
        {
            transform_.mmRotate_ = TotalMx;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, Angle);

        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(Up) != XMVectorGetX(vNormal) || XMVectorGetY(Up) != XMVectorGetY(vNormal) || XMVectorGetZ(Up) != XMVectorGetZ(vNormal))
    {
        Up = vNormal;
    }
}

//���C(�~�p)
void Enemy::StageRayCast(RayCastData* data)
{
    //�O
    data[Straight].start = transform_.position_;     //���C�̔��ˈʒu
    XMVECTOR moveZ = { 0,0,1 };                      //�������l
    moveZ = XMVector3TransformCoord(moveZ, transform_.mmRotate_);
    XMStoreFloat3(&data[Straight].dir, moveZ);
    Model::RayCast(hGroundModel_, &data[Straight]);  //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    if (data[Straight].dist <= 1)
    {
        XMVECTOR dis = { 0,0,data[Straight].dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, pos - (moveZ - dis));

        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);
        ZERO_INITIALIZE(stateCount_);

        //��Ԃ���]�ɕύX
        aiState_ = ROTATION;

        //�A�j���[�V������~
        Model::SetAnimFlag(hModel_, false);
    }

    if (data[Under].dist >= 1)//3
    {
        XMFLOAT3 moveL;

        XMStoreFloat3(&moveL, (-vNormal) / 10);

        transform_.position_ = { transform_.position_.x + moveL.x, transform_.position_.y + moveL.y, transform_.position_.z + moveL.z };
    }

}

//�L�����̓���
void Enemy::MovingOperation(RayCastData* data)
{
    //��Ԃɂ����Enemy�̍s����ω�������
    switch (aiState_)
    {
    //�ҋ@
    case WAIT:

        //WAIT���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
        if (operationTime_ == ZERO)
        {
            operationTime_ = (rand() % 13 + 6) * 10;
            ZERO_INITIALIZE(stateCount_);
        }

        Wait();
        break;
    //�ړ�
    case MOVE:

        //MOVE���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
        if (operationTime_ == ZERO)
        {
            operationTime_ = (rand() % 19 + 12) * 10;
            ZERO_INITIALIZE(stateCount_);
        }

        Move(data);
        break;
    //��]
    case ROTATION:

        //��]����p�x��ݒ�
        if (rotationAngle_ == ZERO)
        {
            rotationSign_ = rand() % 2 == 1 ? 1 : -1;
            rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
            ZERO_INITIALIZE(stateCount_);
        }

        //��]�͔C�ӂ̊p�x�܂ŉ�]�������Ԃ��ς��
        Rotation();
        break;

    //Player�̕����ֈړ�
    case MOVING_LOOK_PLAYER:


        break;
    //�ǂ�ł��Ȃ���
    default:

        //��Ԃ�ҋ@�ɐݒ�
        aiState_ = WAIT;

        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(stateCount_);

        break;
    }

    //��ԕb�����₷
    stateCount_++;
}


///////////////////AI�s���֐�////////////////////

//�ҋ@
void Enemy::Wait()
{
    //��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);

        //��Ԃ�Move�ɕύX
        aiState_ = MOVE;
    }
}

//�s��
void Enemy::Move(RayCastData* data)
{
    //�A�j���[�V�����J�n
    Model::SetAnimFlag(hModel_, true);

    //XMFLOAT3�^��1Fream�����ʂ��i�[����ϐ�
    XMFLOAT3 move;

    //�i�s�x�N�g�������g�̉�]�s��ŉ�]������move�Ɋi�[(1Fream�����ʂ�0.1�ɂ��Ă���)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) / 10);

    //���g��transform�ɉ��Z
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };

    //�n�`�̍����ɍ��킹��
    //��������������0.9f��菬�����Ȃ�
    if (data[Under].dist < 0.9f)
    {
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&data[Under].pos) + vNormal);
    }

    //��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    if (stateCount_ > operationTime_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);

        //��Ԃ���]�ɐݒ�
        aiState_ = ROTATION;

        //�A�j���[�V������~
        Model::SetAnimFlag(hModel_, false);
    }
}

//��]
void Enemy::Rotation()
{
    //��]
    Angle += 0.02 * rotationSign_;
    rotationTotal_ += 0.02;

    if (Angle > XMConvertToRadians(TWOPI_DEGREES))
        Angle = XMConvertToRadians(ZEROPI_DEGREES);

    //��]�p�x����]�����������Ȃ�����
    if (rotationTotal_ > rotationAngle_)
    {
        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);

        //��Ԃ�ҋ@�ɐݒ�
        aiState_ = WAIT;
    }
}

//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
void Enemy::PlayerNearWithIsCheck()
{
    //����Player�̃|�C���^��Nullptr�ɂȂ��Ă����珈�������Ȃ�
    if (pPlayer_ == nullptr) return;

    //Player�̃|�W�V�����Q�b�g
    XMFLOAT3 playerPos = pPlayer_->GetPosition();

    //���g����Player�ւ̃x�N�g��
    XMVECTOR vToPlayer = XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_);

    //���g����Player�ւ̃x�N�g���Ǝ��g�̑O�x�N�g���Ƃ̓��ς𒲂ׂ�
    float dotX = XMVectorGetX(XMVector3AngleBetweenNormals(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer)));

    //���p��,�w�苗�����ɂ���Ȃ�
    if (dotX < XMConvertToRadians(50) && dotX > XMConvertToRadians(-50) &&
        Transform::RangeCalculation(playerPos, transform_.position_) < 15.0f)
    {
        transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal, dotX);
        aiState_ = MOVE;
    }
}

//Player�̕����ֈړ�
void Enemy::MovingLookPlayer()
{
    
}
