#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//�����V�[�����Ǘ�����N���X
class Player : public GameObject
{
	int      hModel_;                      //���f���ԍ�

	///////////////�J����///////////////////

	XMFLOAT3       cameraPos_;             //�J�����̊p�x
	const XMVECTOR CAM_VEC;                //Player����J�����܂ł̋���  
	

	///////////////�����蔻��///////////////////

	Stage* pstage_;                        //�X�e�[�W�N���X�̃|�C���^
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

	XMVECTOR Up;

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

	//�v���C���[����
	void MovingOperation();

	//�������Ǝ��̊p�x�Ɍ���
	void FaceOrientationSlowly(float afterRotate, bool& flag);

	//���C
	void StageRayCast();
};

