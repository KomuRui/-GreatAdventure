#pragma once
#include "Engine/GameObject.h"
#include "TutorialScene/TutorialStage.h"
#include "windowsnumerics.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"

using namespace Windows::Foundation::Numerics;

//�����V�[�����Ǘ�����N���X
class Player : public GameObject
{
	///////////////�L�����̕K�v�ȏ��///////////////////
	Particle* pParticle_;

	XMMATRIX mPreviousAngle;               //�W�����v���Ă���Ƃ��̃}�g���N�X
	XMMATRIX TotalMx;					   //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

	XMVECTOR front;                        //�L�����̑O�����̃x�N�g��
	XMVECTOR Up;                           //�L�����̏�x�N�g��
	XMVECTOR Down;					       //�L�����̉��x�N�g��
	XMVECTOR vNormal;                      //�L�����̉��̃X�e�[�W�̖@��
	XMVECTOR vJamp;                        //�W�����v����Ƃ��̌��ƂȂ��x�N�g��
	XMVECTOR KeepJamp;                     //���ƂƂȂ�W�����v�x�N�g����ۑ����Ă���

	float Angle;                           //�L�����̏�̎��̊p�x
	float JampRotationPreviousAngle;       //�W�����v���Ă���Ƃ��̊p�x

    int   hModel_;                         //���f���ԍ�
	int   rotationCount;                   //��]���Ă���ǂ̂��炢�̃t���[������������

	bool  isJamp;                          //���W�����v���Ă��邩
	bool  isJampRotation;                  //���W�����v��]���Ă��邩
	bool  isRotation;                      //����]�����Ă��邩


	///////////////�J����///////////////////

	enum Cam
	{
		LONG,                              //������
		SHORT,                             //�ߋ���
		MAX_CAM_SIZE
	};

	XMVECTOR CAM_VEC[MAX_CAM_SIZE];        //Player����J�����܂ł̋���  
	XMMATRIX CamMat;                       //�J�����̊p�x��ύX���邽�߂̃}�g���N�X
	
    int   camStatus_;                      //�J�����̏��
	float camAngle_;                       //�J�����̊p�x

	///////////////�����蔻��///////////////////

	TutorialStage* pstage_;                //�X�e�[�W�N���X�̃|�C���^
	int      hGroundModel_;                //�X�e�[�W�̃��f���ԍ�������ϐ�

	enum StageRayDecision                  //�e�����ւ̓����蔻�肷�邽�߂ɗ񋓂���
	{
		Straight = 0,                      //�O
		Back,                              //��
		Left,                              //��
		Right,                             //�E
		Under,                             //��
		Top,                               //��
		MAX_RAY_SIZE
	};

	float acceleration;             //�d�͂̉����x
	

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

	//�X�e�[�W�ɍ��킹��Player����]
	void RotationInStage();

	//�������Ǝ��̊p�x�Ɍ���
	void FaceOrientationSlowly(float afterRotate, bool& flag);

	//���C(�~�p)
	void StageRayCast(RayCastData* data);

	//���C(2D�p)
	void StageRayCast2D();

	//�v���C���[����(�~�p)
	void MovingOperation(RayCastData* data);

	//�v���C���[����(2D�p)
	void MovingOperation2D();

	//��]�G�t�F�N�g
	void RotationEffect();

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	//Player��^�t�̏�Ԃɐݒ�(�܂��������΂ɐݒ肷��ƊO�ς��O�ɂȂ��Ă��܂��̂ŏ������炷)
	void SetInverseNormalAndDown() { vNormal = -vNormal; vNormal += {0, 0.1, 0, 0}; Down = -vNormal; }

	//Player����]�����Ă��邩
	bool GetRotationFlag() { return (isRotation || isJampRotation); }
};

