#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

/// <summary>
/// �������N���X
/// </summary>
class MoveFloor : public Mob
{
private:

	//�ϐ�
	int      status_;          //���
	XMFLOAT3 MoveFloorTarget_; //���[�v�̈ړ���

	//���
	enum Status
	{
		STOP,      //��~���
		MOVE,      //�������
		MAX_STATUS
	};

public:

	//�R���X�g���N�^
	MoveFloor(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~MoveFloor();

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	/// <summary>
	/// ���̖ړI�n�܂ňړ�
	/// </summary>
	void MovingToPurpose();

	/// <summary>
	/// ���[�v�̈ړ���ݒ�
	/// </summary>
	/// <param name="target">�ݒ肵�������[�v�̈ړ���</param>
	void SetMoveFloorTarget(const XMFLOAT3& target) { MoveFloorTarget_ = target; }

	/// <summary>
	/// �����悤�ɃZ�b�g
	/// </summary>
	void SetMove() {  status_ = MOVE; }

};

