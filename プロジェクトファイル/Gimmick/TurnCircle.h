#pragma once
#include "../Mob/Mob.h"
#include "../Engine/Component/Posture.h"

/// <summary>
/// �~�j�Q�[���̓o�ꂷ��M�~�b�N�̉��~
/// </summary>
class TurnCircle : public Mob
{
	//�������p���ɂ��Ă����R���|�[�l���g
	Posture posture_;

	//��]�p�x
	float rotationAngle_;

public:

	//�R���X�g���N�^
	TurnCircle(GameObject * parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	/////////////////////�֐�//////////////////////

	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();

};

