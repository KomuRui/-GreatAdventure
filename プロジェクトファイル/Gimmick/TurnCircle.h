#pragma once
#include "../Mob.h"

/// <summary>
/// �~�j�Q�[���̓o�ꂷ��M�~�b�N�̉��~
/// </summary>
class TurnCircle : public Mob
{

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

	/// <summary>
	/// �^���̖@���𒲂ׂăL�����̏㎲�����肷��
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void CheckUnderNormal(const RayCastData& data);

	/// <summary>
	/// ���C�œ����蔻��(3D�p)
	/// </summary>
	/// <param name="data">�����蔻��ɕK�v�ȃf�[�^</param>
	void StageRayCast(const RayCastData& data);

};

