#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

//�������N���X
class MoveFloor : public Mob
{
private:

	//�ϐ�
	int      status_;          //���
	int      number_;          //���[�v�̔ԍ�
	XMFLOAT3 MoveFloorTarget_; //���[�v�̈ړ���

	//���
	enum Status
	{
		STOP,
		MOVE,
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

	//���̖ړI�n�܂ňړ�
	void MovingToPurpose();

	//���[�v�̔ԍ��Z�b�g
	void SetNumber(const int& num) { number_ = num; }

	//���[�v�̈ړ���ݒ�
	void SetMoveFloorTarget(const XMFLOAT3& target) { MoveFloorTarget_ = target; }

};

