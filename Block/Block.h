#pragma once
#include "../Mob.h"

class Block : public Mob
{
protected:

	XMFLOAT3 hitMovePos_; //Player�ƏՓ˂����ꍇ�̃u���b�N�̃|�W�V����
	bool     isHit_;      //Player�Ɠ������Ă��邩

public:
	//�R���X�g���N�^
	Block(GameObject* parent, std::string modelPath, std::string name);

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	///////////�Z�b�^�[////////////

	//�������Ă��邩
	void SetIsHit(bool flag) { isHit_ = flag; }

	///////////////////�p����p�֐�/////////////////////

	//�p���悲�Ƃ�Update�ł̓�������ς���
	virtual void BlockChildUpdate() {};

	//�p����p�̏�����
	virtual void BlockChildInitialize() {};

	//�p����p�̕`��
	virtual void BlockChildDraw() {};

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	virtual void BlockChildStartUpdate() {};

	//Player�������瓖���������̋���
	virtual void HitToLowerPlayer();

	//�p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	virtual void OnCollision(GameObject* pTarget) override {};

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	virtual void TimeMethod() override {};

};

