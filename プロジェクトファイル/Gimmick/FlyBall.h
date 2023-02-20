#pragma once
#include "../Mob.h"
#include "../Engine/Component/Posture.h"
#include "../Engine/Component/EasingMove.h"

/// <summary>
/// �{�X�V�[���ɓo�ꂵ�Ă���Player����΂��čU�����邽�߂̃M�~�b�N
/// </summary>
class FlyBall : public Mob
{
	//���ł��邩�ǂ���
	bool isFly_;

	//�������|�W�V�����ɖ߂��Ă��邩�ǂ���
	bool isReturnPos;

	//��]����Ƃ��̊p�x
	float rotateAngle_;

	//�C�[�W���O�ňړ����鎞�ɕK�v�ȕϐ�
	EasingMove* pEasing_;

	//�x�[�X�̈ʒu
	XMFLOAT3 basePos_;

public:

	//�R���X�g���N�^
	FlyBall(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//////////////////////////////�֐�//////////////////////////////

	/// <summary>
	/// ���
	/// </summary>
	void Fly();
};

