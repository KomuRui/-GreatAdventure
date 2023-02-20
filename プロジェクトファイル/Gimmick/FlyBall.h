#pragma once
#include "../Mob.h"
#include "../Engine/Component/Posture.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// �{�X�V�[���ɓo�ꂵ�Ă���Player����΂��čU�����邽�߂̃M�~�b�N
/// </summary>
class FlyBall : public Mob
{
	int hStickModel_;     //FlyBall�̖_�̃��f���ԍ�
	Transform tStick_;    //�_�p�̃g�����X�t�H�[��
	
	bool isFly_;          //���ł��邩�ǂ���
	bool isReturnPos;     //�������|�W�V�����ɖ߂��Ă��邩�ǂ���

	float rotateAngle_;   //��]����Ƃ��̊p�x

	EasingMove* pEasing_; //�C�[�W���O�ňړ����鎞�ɕK�v�ȕϐ�

	XMFLOAT3 beforePos_;  //�ړ��O�̈ʒu
	XMFLOAT3 basePos_;    //�x�[�X�̈ʒu

	XMVECTOR baseUp_;     //�x�[�X�̏�x�N�g��

public:

	//�R���X�g���N�^
	FlyBall(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	//////////////////////////////�֐�//////////////////////////////

	/// <summary>
	/// ���
	/// </summary>
	void Fly();

	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();

	/// <summary>
	/// �_�̃g�����X�t�H�[���̌v�Z
	/// </summary>
	void StickCalculation();
};

