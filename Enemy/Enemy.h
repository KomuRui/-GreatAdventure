#pragma once
#include "../Mob.h"
#include "../TutorialScene/TutorialStage.h"

class Enemy : public Mob
{
protected:

	///////////////�G�̓����p�^�[��////////////////

	int aiState_;         //���݂̓����̏��
	int operationTime_;   //���̏�Ԃɕς��܂ł̎���

	XMVECTOR moveDir_;    //�L��������������

	//AI�̍s���s���̏���
	enum EnemyAiState
	{
		MOVE,             //�ړ�
		WAIT,             //�ҋ@
		ROTATION,         //��]
		MAX_AI_STATE
	};

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

	XMVECTOR Up;                    //�L�����̏�x�N�g��
	XMVECTOR Down;                  //�L�����̉��x�N�g��
	XMVECTOR vNormal;               //���̖@��
	float Angle;                    //�L�����̏�̎��̊p�x

	XMMATRIX TotalMx;               //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

public:
	//�R���X�g���N�^
	Enemy(GameObject* parent, std::string modelPath);

	//������
	void ChildInitialize() override;

	//�X�V
	void UpdateMove() override;

	//�`��
	void ChildDraw() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate();

	//�X�e�[�W�ɍ��킹�ăL��������]
	void RotationInStage();

	//���C(�~�p)
	void StageRayCast();

	//�L�����̓���(�~�p)
	void MovingOperation();

	///////////////////AI�s���֐�/////////////////////

	//�ҋ@
	void Wait();

	//�ړ�
	void Move();

	//��]
    void Rotation();
};

