#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"

//���[�v�N���X
class Warp : public Mob
{
private:

	//�萔
	const float    ROTATION_QUANTITY = 0.02f;        //��]��
	const float    ADDITION_TURNOVERRATE = 0.03f;    //��]�������Z�����
	const float    MAX_TURNOVERRATE = 10.0f;         //�ő��]��
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };     //�R���C�_�[�|�W�V����
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 }; //�R���C�_�[�T�C�Y

	//�ϐ�
	float    turnoverRate_;  //��]��
	int      status_;        //���
	int      number_;        //���[�v�̔ԍ�
	XMFLOAT3 playerPos_;     //���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	PolyLine* pLine[3];

	//���[�v�ɏ��
	enum Status
	{
		STOP,
		MOVE,
		MAX_STATUS
	};

public:

	//�R���X�g���N�^
	Warp(GameObject* parent, std::string modelPath, std::string name);

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	//�p����p�̕`��
	void ChildDraw() override;

	//���̐��܂ňړ�
	void MovingToStar();

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//���[�v�̔ԍ��Z�b�g
	void SetNumber(int num) { number_ = num; }
};

