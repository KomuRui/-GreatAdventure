#include "PlayerBase.h"
#include "../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

////�萔
namespace
{
    //Player�̃p�����[�^��ۑ����Ă���p�X
    LPCTSTR parameterPath = "Parameter/Player/PlayerParameter.ini";

    ///////////////�L�����̕K�v�ȏ��///////////////////

    static const float NORMAL_INTERPOLATION_FACTOR = GetPrivateProfilefloat("PLAYER", "NormalFactor", "0.045", parameterPath); //�@�����Ԃ���Ƃ��̕�ԌW��
    static const float PLAYER_ANIM_SPEED = GetPrivateProfilefloat("PLAYER", "AnimSpeed", "1.0", parameterPath);                //�A�j���[�V�����̍Đ����x
    static const int ANIM_START_FRAME = GetPrivateProfilefloat("PLAYER", "AnimStartFrame", "1", parameterPath);                //�A�j���[�V�����̊J�n�t���[��
    static const int ANIM_END_FRAME = GetPrivateProfilefloat("PLAYER", "AnimEndFrame", "60", parameterPath);			       //�A�j���[�V�����̏I���t���[��
    static const int MAX_NORMAL_RADIANS = GetPrivateProfilefloat("PLAYER", "MaxNormalRadians", "50", parameterPath);   	       //�@���Ƃ̍ő�p�x			
    static const float PLAYER_MODEL_SIZE_X = 1.0f;  //Player��X�̃��f���T�C�Y
    static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //Player��Y�̃��f���T�C�Y
    static const float GRAVITY_ADDITION = 0.03f;    //�d�͂̉��Z�l

    ////////////////���C�g///////////////////

    static const float LIGHT_POS_Z = GetPrivateProfilefloat("LIGHT", "LightZPos", "2", parameterPath);  //���C�g��Z�̃|�W�V����

    ////////////////�J����///////////////////

    static const float CAMERA_INTERPOLATION_FACTOR = GetPrivateProfilefloat("CAMERA", "CamFactor", "0.08", parameterPath);  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
    static const float CAM_POS_2D_Z = GetPrivateProfilefloat("CAMERA", "CamPos2DZ", "20", parameterPath);                   //2D�̎��̃J������Z�̈ʒu
    static const float CAM_SHOULDER_ADD_VALUE = 0.5f; //�V�����_�[�ŃJ�������삷�鎞�̉��Z����l
    static const float CAM_STICR_ADD_VALUE = 0.03f;   //�X�e�B�b�NR�ŃJ�����𑀍삷��Ƃ��̉��Z����l

    ////////////////�R���C�_�[///////////////////

    static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO };  //�R���C�_�[�̈ʒu
    static const float    COLLIDER_SIZE = 1.0f;               //�R���C�_�[�̃T�C�Y
}

//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent)
    :Mob(parent, "Star_Main_Character.fbx", "Player"),

    ///////////////�L�����̕K�v�ȏ��///////////////////

    //�L�����̎���]�ɕK�v�ȕϐ�
    jampRotationPreviousAngle_(ZERO),
    normalFlag_(true),

    //���̑�
    acceleration_(1),
    pState_(new PlayerStateManager),

    ///////////////////�J����///////////////////////

    camMat_(XMMatrixIdentity()),
    camStatus_(LONG),
    camAngle_(1),
    camPosFlag_(true),
    camFlag_(true)

{
    camVec_[LONG] = XMVectorSet(ZERO, 15, -15, ZERO);
    camVec_[SHORT] = XMVectorSet(ZERO, 4, -4, ZERO);
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void PlayerBase::ChildInitialize()
{
    ///////////////////������///////////////////////

    //���
    ARGUMENT_INITIALIZE(PlayerStateManager::playerState_ ,PlayerStateManager::playerStanding_);

    //��]���鎞��]�s����g���悤�ɂ���
    ARGUMENT_INITIALIZE(transform_.mFlag_,true);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
    AddCollider(collision);

    ///////////////�G�t�F�N�g�ƃA�j���[�V�����ݒ�///////////////////

    //�G�t�F�N�g�o�����߂ɕK�v
    PlayerEffectManager::Initialize(this);

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void PlayerBase::ChildStartUpdate()
{
    //���g�̃|�W�V�����Z�b�g
    ARGUMENT_INITIALIZE(transform_.position_, pstage_->GetPos());
}

//�X�V
void PlayerBase::Update()
{
    //�^���̖@���𒲂ׂ�
    CheckUnderNormal();

    //�p����p�̍X�V
    ChildPlayerUpdate();

    //�J�����̋���
    CameraBehavior();
}


