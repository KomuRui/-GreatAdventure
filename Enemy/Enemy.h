#pragma once
#include "../Mob.h"
#include "../TutorialScene/TutorialStage.h"
#include "../Engine/Fbx.h"
#include "../Player.h"

class Enemy : public Mob
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////

	XMVECTOR front_;        //�L�����̑O�����̃x�N�g��

	///////////////�G�̓����p�^�[��////////////////

	int aiState_;           //���݂̓����̏��
	int operationTime_;     //���̏�Ԃɕς��܂ł̎���
	int stateCount_;        //���̏�ԂɂȂ��Ă���ǂ̂��炢�̕b����������
	int rotationAngle_;     //��]�p�x
	int rotationSign_;      //��]����
	float dotX_;            //���ς̌v�Z�����l������
	float rotationTotal_;   //�ǂ̂��炢��]������
	Player* pPlayer_;       //�v���C���[�̏��

	//AI�̍s���s���̏���
	enum EnemyAiState
	{
		MOVE,               //�ړ�
		WAIT,               //�ҋ@
		ROTATION,           //��]
		KNOCKBACK_DIE,      //�m�b�N�o�b�N���S
		DIE,                //���ʂ̎��S
		MAX_AI_STATE
	};

	///////////////�����蔻��///////////////////

	int    hGroundModel_;   //�X�e�[�W�̃��f���ԍ�������ϐ�

	enum StageRayDecision   //�e�����ւ̓����蔻�肷�邽�߂ɗ񋓂���
	{
		Straight = 0,       //�O
		Back,               //��
		Left,               //��
		Right,              //�E
		Under,              //��
		Top,                //��
		MAX_RAY_SIZE
	};

	float acceleration;     //�d�͂̉����x


public:
	//�R���X�g���N�^
	Enemy(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�e�[�W�ɍ��킹�ăL��������]
	void RotationInStage();

	//���C(�~�p)
	void StageRayCast(RayCastData* data);

	//�L�����̓���(�~�p)
	void MovingOperation(RayCastData* data);

	///////////////////AI�p�֐�/////////////////////

	//�ҋ@
	void Wait();

	//�ړ�
	void Move(RayCastData* data);

	//��]
    void Rotation();

	//�m�b�N�o�b�N���Ď��S
	virtual void KnockBackDie() {};

	//���S
	virtual void Die() {};

	//Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	void PlayerNearWithIsCheck();

	//Player�̕����ֈړ�
	void MovingLookPlayer();

	///////////////////�p����p�֐�/////////////////////

	//�p���悲�Ƃ�Update�ł̓�������ς���
	virtual void EnemyChildUpdate() {};

	//�p����p�̏�����
	virtual void EnemyChildInitialize() {};

	//�p����p�̕`��
	virtual void EnemyChildDraw() {};

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	virtual void EnemyChildStartUpdate() {};

	//Player�����p���A�w�苗�����ɂ������̏���(�p���p)
	virtual void PlayerWithIf() {};

	//Player�����p���A�w�苗�����ɂ��Ȃ����̏���(�p���p)
	virtual void NotPlayerWithIf() {};
	 
	//�p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	virtual void OnCollision(GameObject* pTarget) override {};

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	virtual void TimeMethod() override {};
};

