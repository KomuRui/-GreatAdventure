#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"


class Player : public GameObject
{

	///////////////�L�����̕K�v�ȏ��///////////////////

	//�萔
	const XMVECTOR UP_VECTOR = { 0,1,0,0 };          //��x�N�g��
	const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
	const float RUN_SPEED = 1.5f;                    //�����Ă���Ƃ��̃L�����̃X�s�[�h
	const float ANIM_SPEED = 1.0f;                   //�A�j���[�V�����̍Đ����x
	const float ANIM_RUN_SPEED = 2.0f;               //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
	const int ANIM_START_FRAME = 1;                  //�A�j���[�V�����̊J�n�t���[��
	const int ANIM_END_FRAME = 60;					 //�A�j���[�V�����̏I���t���[��
	const int MAX_NORMAL_RADIANS = 50;				 //�@���Ƃ̍ő�p�x

	//�ϐ�

	Particle* pParticle_;                   //�G�t�F�N�g�\������̂ɕK�v�ȕϐ�
	 
	XMMATRIX mPreviousAngle_;               //�W�����v���Ă���Ƃ��̃}�g���N�X
	XMMATRIX totalMx_;					    //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

	XMVECTOR front_;                        //�L�����̑O�����̃x�N�g��
	XMVECTOR up_;                           //�L�����̏�x�N�g��
	XMVECTOR down_;					        //�L�����̉��x�N�g��
	XMVECTOR vNormal_;                      //�L�����̉��̃X�e�[�W�̖@��
	XMVECTOR vJamp_;                        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR keepJamp_;                     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

	float angle_;                           //�L�����̏�̎��̊p�x
	float jampRotationPreviousAngle_;       //�W�����v���Ă���Ƃ��̊p�x
	float acceleration_;                    //�d�͂̉����x

    int   hModel_;                          //���f���ԍ�
	int   rotationCount_;                   //��]���Ă���ǂ̂��炢�̃t���[������������

	bool  isJamp_;                          //���W�����v���Ă��邩
	bool  isJampRotation_;                  //���W�����v��]���Ă��邩
	bool  isRotation_;                      //����]�����Ă��邩
	bool  isFly_;                           //�������Ă��邩�ǂ���
	bool  normalFlag_;                      //�@���𒲂ׂ邩�ǂ���

	///////////////�J����///////////////////

	//�萔

	const float CAMERA_INTERPOLATION_FACTOR = 0.08;  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
	const float CAM_POS_2D_Z = 20;                   //2D�̎��̃J������Z�̈ʒu

	//�ϐ�

	enum Cam
	{
		LONG,          //������
		SHORT,         //�ߋ���
		MAX_CAM_SIZE
	};

	XMVECTOR camVec_[MAX_CAM_SIZE];    //Player����J�����܂ł̋���  
	XMMATRIX camMat_;                  //�J�����̊p�x��ύX���邽�߂̃}�g���N�X
	
    int   camStatus_;                  //�J�����̏��
	float camAngle_;                   //�J�����̊p�x
	bool  camPosFlag_;                 //�J�����̃|�W�V�����������ǂ���

	///////////////���C�g///////////////////
	
	//�萔

	const float LIGHT_POS_Z = 2;       //���C�g��Z�̃|�W�V����

	///////////////�����蔻��///////////////////

	//�萔

	const XMFLOAT3 COLLIDER_POS  = { 0,0,0 }; //�R���C�_�[�̈ʒu
	const float    COLLIDER_SIZE = 1.0f;      //�R���C�_�[�̃T�C�Y

	//�ϐ�

	Stage* pstage_;                           //�X�e�[�W�N���X�̃|�C���^
	int      hGroundModel_;                   //�X�e�[�W�̃��f���ԍ�������ϐ�

	enum StageRayDecision                     //�e�����ւ̓����蔻�肷�邽�߂ɗ񋓂���
	{
		Straight = 0,                         //�O
		Back,                                 //��
		Left,                                 //��
		Right,                                //�E
		Under,                                //��
		Top,                                  //��
		MAX_RAY_SIZE
	};
	

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	/////////////////////�֐�//////////////////////

	//�J�����̏���
	void CameraBehavior();

	//�^���̖@���𒲂ׂ�
	void CheckUnderNormal(RayCastData* data);

	//�X�e�[�W�ɍ��킹��Player����](3D�p)
	void RotationInStage();

	//�X�e�[�W�ɍ��킹��Player����](2D�p)
	void RotationInStage2D();

	//���C(3D�p)
	void StageRayCast(RayCastData* data);

	//���C(2D�p)
	void StageRayCast2D();

	//�v���C���[����(3D�p)
	void MovingOperation(RayCastData* data);

	//�v���C���[����(2D�p)
	void MovingOperation2D();

	//��]�G�t�F�N�g
	void RotationEffect();

	//�����G�t�F�N�g
	void FallEffect();

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	//Player��^�t�̏�Ԃɐݒ�(�܂��������΂ɐݒ肷��ƊO�ς��O�ɂȂ��Ă��܂��̂ŏ������炷)
	void SetInverseNormalAndDown() { vNormal_ += {0, 0.1, 0, 0}; vNormal_ = -vNormal_;down_ = -vNormal_; }

	//�J�����𓮂����Ȃ��Z�b�g
	void SetCamPosFlag() { camPosFlag_ = false; }

	//�@�����ׂ邩�ǂ����Z�b�g
	void SetNormalFlag(const bool& flag) { normalFlag_ = flag; }

	//Player����]�����Ă��邩
	bool GetRotationFlag() { return (isRotation_ || isJampRotation_); }

	//�@���Q�b�g
	XMVECTOR GetNormal() { return vNormal_; }
};

