#pragma once
#include "../Mob.h"
#include "../TutorialScene/TutorialStage.h"
#include "../Engine/Fbx.h"

class Enemy : public Mob
{
protected:

	///////////////�G�̓����p�^�[��////////////////

	int aiState_;           //���݂̓����̏��
	int operationTime_;     //���̏�Ԃɕς��܂ł̎���
	int stateCount_;        //���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������
	int rotationAngle_;     //��]�p�x
	float rotationTotal_;   //�ǂ̂��炢��]������

	XMVECTOR moveDir_;      //�L��������������

	//AI�̍s���s���̏���
	enum EnemyAiState
	{
		MOVE,             //�ړ�
		WAIT,             //�ҋ@
		ROTATION,         //��]
		MAX_AI_STATE
	};

	///////////////�����蔻��///////////////////

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

	float acceleration;                    //�d�͂̉����x


public:
	//�R���X�g���N�^
	Enemy(GameObject* parent, std::string modelPath, std::string name);

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
	void StageRayCast(RayCastData* data);

	//�L�����̓���(�~�p)
	void MovingOperation(RayCastData* data);

	///////////////////AI�s���֐�/////////////////////

	//�ҋ@
	void Wait();

	//�ړ�
	void Move(RayCastData* data);

	//��]
    void Rotation();
};

