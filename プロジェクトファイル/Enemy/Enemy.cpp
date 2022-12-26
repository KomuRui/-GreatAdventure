#include "Enemy.h"
#include "../Engine/Model.h"

////�萔
namespace
{
    static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
    static const int MAX_NORMAL_RADIANS = 50;               //�@���Ƃ̍ő�p�x
    static const float RAY_HIT_DISTANCE = 1.0f;             //���C�̓�����������
    static const float GRAVITY_STRENGTH = 0.083f;           //�d�͂̋���
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath,name),acceleration(1), aiState_(MOVE), operationTime_(ZERO), hGroundModel_(-1), stateCount_(ZERO),
    rotationAngle_(ZERO), rotationTotal_(ZERO), front_(XMVectorSet(ZERO, ZERO,1, ZERO)), dotX_(ZERO), rotationSign_(1),
    pState_(new EnemyState)
{
}

//������
void Enemy::ChildInitialize()
{
    EnemyChildInitialize();
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Enemy::ChildStartUpdate()
{

    //������Ԃ̐ݒ�
    ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

    ///////////////Stage�̃f�[�^�擾///////////////////

    //���f���ԍ��擾
    hGroundModel_ = pstage_->GethModel();

    ///////////////�p����p�̏�����///////////////////

    EnemyChildStartUpdate();

}

//�X�V
void Enemy::ChildUpdate()
{

    //�������Ŏg���̂Ő�ɐ錾���Ă���
    RayCastData downData;
    downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
    downData.dir = VectorToFloat3(down_);          //���C�̕���
    Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

    //�^���̖@���𒲂ׂăL�����̏㎲�����肷��
    CheckUnderNormal(downData);

    //Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
    PlayerNearWithIsCheck();

    //�L�����̓���
    MovingOperation();

    //�p����p�̃A�b�v�f�[�g
    EnemyChildUpdate();

    //�X�e�[�W�Ƃ̓����蔻��
    StageRayCast(downData);
}

//�`��
void Enemy::ChildDraw()
{
    //�p����p�̕`��
    EnemyChildDraw();
}

//�^���̖@���𒲂ׂăL�����̏㎲�����肷��
void Enemy::CheckUnderNormal(const RayCastData& data)
{
    if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
    {
        //���̃L�����̏�x�N�g��vNormal�Ɖ��̖@���̓��ς����߂�
        float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

        //�p�x��50�x�ȓ��Ɏ��܂��Ă�����(�ǂƂ��ɏ�点�Ȃ�����)
        if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
        {
            //������ƕ��
            vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
            down_ = -vNormal_;
        }
    }
}

//�X�e�[�W�ɍ��킹��Player����]
void Enemy::RotationInStage()
{
    //X�̃x�N�g���𔲂����
    float dotX = 0;

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(XMVector3Normalize(up_), XMVector3Normalize(vNormal_));

        //X�̃x�N�g���𔲂����
        dotX = XMVectorGetX(vecDot);
    }

    XMVECTOR cross = XMVector3Cross(up_, vNormal_);

    if (!pstage_->GetthreeDflag())
    {

        totalMx_ = XMMatrixIdentity();
        transform_.mmRotate_ = totalMx_;

        transform_.mmRotate_ *= XMMatrixRotationAxis(UP_VECTOR, angle_);

    }
    else
    {
        if (dotX != 0 && dotX <= 1 && dotX >= -1)
        {
            totalMx_ *= XMMatrixRotationAxis(cross, acos(dotX));
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);
        }
        else
        {
            transform_.mmRotate_ = totalMx_;
            transform_.mmRotate_ *= XMMatrixRotationAxis(vNormal_, angle_);

        }
    }

    //���L�����܂ł̃x�N�g���Ǝ��L�����̐^��̃x�N�g���������ł��Ⴄ�Ȃ�
    if (XMVectorGetX(up_) != XMVectorGetX(vNormal_) || XMVectorGetY(up_) != XMVectorGetY(vNormal_) || XMVectorGetZ(up_) != XMVectorGetZ(vNormal_))
    {
        up_ = vNormal_;
    }
}

//���C(�~�p)
void Enemy::StageRayCast(const RayCastData& data)
{
    //�O
    RayCastData straightData;
    straightData.start = transform_.position_;                                                          //���C�̃X�^�[�g�ʒu
    straightData.dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_));  //���C�̕���
    Model::AllRayCast(hGroundModel_, &straightData);                                                    //���C�𔭎�

    //////////////////////////////�͂ݏo������������//////////////////////////////////////

    //�O�̋�����1.0�ȉ��Ȃ�
    if (straightData.dist <= RAY_HIT_DISTANCE)
    {
        XMVECTOR dis = { ZERO,ZERO,straightData.dist };
        dis = XMVector3TransformCoord(dis, transform_.mmRotate_);
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVector3TransformCoord(STRAIGHT_VECTOR, transform_.mmRotate_) - dis));

        //0�ɏ�����
        ZERO_INITIALIZE(operationTime_);
        ZERO_INITIALIZE(rotationTotal_);
        ZERO_INITIALIZE(rotationAngle_);
        ZERO_INITIALIZE(stateCount_);

        //��Ԃ���]�ɕύX
        ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

        //�A�j���[�V������~
        Model::SetAnimFlag(hModel_, false);
    }

    //���̋�����1.0�ȏ�Ȃ�
    if (data.dist >= RAY_HIT_DISTANCE)
    {
        transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
    }

}

//�L�����̓���
void Enemy::MovingOperation()
{
    //��Ԃ̍X�V���Ă�
    pState_->Update3D(this);
    ////��Ԃɂ����Enemy�̍s����ω�������
    //switch (aiState_)
    //{
    ////�ҋ@
    //case WAIT:

    //    //WAIT���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
    //    if (operationTime_ == ZERO)
    //    {
    //        operationTime_ = (rand() % 13 + 6) * 10;
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    Wait();
    //    break;
    ////�ړ�
    //case MOVE:

    //    //MOVE���玟�̏�Ԃɕς��܂ł̎��Ԃ�ݒ�
    //    if (operationTime_ == ZERO)
    //    {
    //        operationTime_ = (rand() % 19 + 12) * 10;
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    Move();
    //    break;
    ////��]
    //case ROTATION:

    //    //��]����p�x��ݒ�
    //    if (rotationAngle_ == ZERO)
    //    {
    //        rotationSign_ = rand() % 2 == 1 ? 1 : -1;
    //        rotationAngle_ = XMConvertToRadians((rand() % 141) + 40);
    //        ZERO_INITIALIZE(stateCount_);
    //    }

    //    //��]�͔C�ӂ̊p�x�܂ŉ�]�������Ԃ��ς��
    //    Rotation();
    //    break;

    ////�m�b�N�o�b�N���Ď��S
    //case KNOCKBACK_DIE:

    //    KnockBackDie();
    //    break;

    ////���S
    //case DIE:

    //    Die();
    //    break;

    ////�ǂ�ł��Ȃ���
    //default:

    //    //��Ԃ�ҋ@�ɐݒ�
    //    aiState_ = WAIT;

    //    //0�ɏ�����
    //    ZERO_INITIALIZE(operationTime_);
    //    ZERO_INITIALIZE(stateCount_);

    //    break;
    //}

    ////��ԕb�����₷
    //stateCount_++;
}


///////////////////AI�s���֐�////////////////////

//�ҋ@
void Enemy::Wait()
{
    ////��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    //if (stateCount_ > operationTime_)
    //{
    //    //0�ɏ�����
    //    ZERO_INITIALIZE(operationTime_);

    //    //��Ԃ�Move�ɕύX
    //    aiState_ = MOVE;
    //}
}

//�s��
void Enemy::Move()
{
    //�A�j���[�V�����J�n
    Model::SetAnimFlag(hModel_, true);

    //XMFLOAT3�^��1Fream�����ʂ��i�[����ϐ�
    XMFLOAT3 move = { ZERO,ZERO,ZERO };

    //�i�s�x�N�g�������g�̉�]�s��ŉ�]������move�Ɋi�[(1Fream�����ʂ�0.1�ɂ��Ă���)
    XMStoreFloat3(&move,XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) / 10);

    //���g��transform�ɉ��Z
    transform_.position_ = { transform_.position_.x + move.x,transform_.position_.y + move.y,transform_.position_.z + move.z };

    //�������킹�邽�߂Ƀ��C���΂�
    RayCastData downData;
    downData.start = transform_.position_;         //���C�̃X�^�[�g�ʒu
    downData.dir = VectorToFloat3(down_);          //���C�̕���
    Model::AllRayCast(hGroundModel_, &downData);   //���C�𔭎�(All)

    //�n�`�̍����ɍ��킹��
    //��������������0.9f��菬�����Ȃ�
    if (downData.dist < 0.9f)
        XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

    ////��Ԃ���ԕω��̎��Ԃ��傫���Ȃ�����
    //if (stateCount_ > operationTime_)
    //{
    //    //0�ɏ�����
    //    ZERO_INITIALIZE(operationTime_);

    //    //��Ԃ���]�ɐݒ�
    //    aiState_ = ROTATION;

    //    //�A�j���[�V������~
    //    Model::SetAnimFlag(hModel_, false);
    //}
}

//��]
void Enemy::Rotation()
{
    ////��]
    //angle_ += 0.02 * rotationSign_;
    //rotationTotal_ += 0.02;


    ////��]�p�x����]�����������Ȃ�����
    //if (rotationTotal_ > rotationAngle_)
    //{
    //    //0�ɏ�����
    //    ZERO_INITIALIZE(operationTime_);
    //    ZERO_INITIALIZE(rotationTotal_);
    //    ZERO_INITIALIZE(rotationAngle_);

    //    //��Ԃ�ҋ@�ɐݒ�
    //    aiState_ = WAIT;
    //}
}

//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
void Enemy::PlayerNearWithIsCheck()
{
    //����Player�̃|�C���^��Null�ɂȂ��Ă����珈�������Ȃ�
    if (GameManager::GetpPlayer() == nullptr) return;

    //Player�̃|�W�V�����Q�b�g
    XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();

    //���g����Player�ւ̃x�N�g��
    XMVECTOR vToPlayer = XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_);

    //���g����Player�ւ̃x�N�g���Ǝ��g�̑O�x�N�g���Ƃ̓��ς𒲂ׂ�
    dotX_ = acos(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer))));

    //�ǂ��������ɉ�]�����邩���߂邽�߂ɊO�ς����߂�
    XMVECTOR cross = XMVector3Cross(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)), XMVector3Normalize(vToPlayer));

    //�������Ⴄ�Ȃ�
    if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(vNormal_)))
        dotX_ *= -1;


    //���p��,�w�苗�����ɂ���Ȃ�
    if (dotX_ < XMConvertToRadians(50) && dotX_ > XMConvertToRadians(-50) &&
        RangeCalculation(playerPos, transform_.position_) < 15.0f)
    {
        //����łȂ��Ȃ�
        if(EnemyStateList::GetEnemyDieState())
            //Player�̕����������߂̊p�x�𑫂�
            angle_ += dotX_;

        //����ł��Ȃ��̂Ȃ�
        if(pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
            ChangeEnemyState(EnemyStateList::GetEnemyMoveState());

        //Player�Ƃ̋�����3�ȓ�������łȂ��̂Ȃ�
        if (RangeCalculation(transform_.position_, GameManager::GetpPlayer()->GetPosition()) < 3 && pState_ != EnemyStateList::GetEnemyKnockBackState() && EnemyStateList::GetEnemyDieState())
            ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

        //�p����p�̊֐�(���p���A�˒�����Player������Ȃ�)
        PlayerWithIf();
    }
    else
        //�p����p�̊֐�(���p���A�˒�����Player���Ȃ��Ȃ�)
        NotPlayerWithIf();
}

//��ԃ`�F���W
void Enemy::ChangeEnemyState(EnemyState* state)
{
    //������Ԃ���Ȃ��̂Ȃ�
    if (pState_ != state)
    {
        //��ԕύX
        ARGUMENT_INITIALIZE(pState_, state);
        pState_->Enter(this);
    }
}

