#pragma once
#include "../Mob.h"
#include "../Engine/Fbx.h"

/// <summary>
/// �G�̊��N���X(�X�e�[�g�x�[�XAI)
/// </summary>
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

	//AI�̍s���s��
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

	/// <summary>
	/// �ҋ@
	/// </summary>
	void Wait();

	/// <summary>
	/// �ړ�
	/// </summary>
	/// <param name="data">���C�L���X�g�̃f�[�^</param>
	void Move(RayCastData* data);

    /// <summary>
    /// ��]
    /// </summary>
    void Rotation();

	/// <summary>
	/// �m�b�N�o�b�N���Ď��S
	/// </summary>
	virtual void KnockBackDie() {};

	/// <summary>
	/// ���S
	/// </summary>
	virtual void Die() {};

	/// <summary>
	/// Player�����p��,�w�苗�����ɂ��邩�ǂ������ׂ�
	/// </summary>
	void PlayerNearWithIsCheck();

	/// <summary>
	/// Player�̕����ֈړ�
	/// </summary>
	void MovingLookPlayer();

	///////////////////�p����p�֐�/////////////////////

	/// <summary>
	/// �p���悲�Ƃ�Update�ł̓�������ς���
	/// </summary>
	virtual void EnemyChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void EnemyChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void EnemyChildDraw() {};

	/// <summary>
	/// �p����p�̃X�^�[�g�A�b�v�f�[�g
	/// </summary>
	virtual void EnemyChildStartUpdate() {};

	/// <summary>
	/// Player�����p���A�w�苗�����ɂ������̏���(�p���p)
	/// </summary>
	virtual void PlayerWithIf() {};

	/// <summary>
	/// Player�����p���A�w�苗�����ɂ��Ȃ����̏���(�p���p)
	/// </summary>
	virtual void NotPlayerWithIf() {};

	/// <summary>
	/// �p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="pTarget">���������I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// �p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	virtual void TimeMethod() override {};
};

