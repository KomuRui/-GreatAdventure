#pragma once
#include "../Mob.h"

/// <summary>
/// �~�j�Q�[���̓o�ꂷ��M�~�b�N�̉��~
/// </summary>
class TurnCircle : public Mob
{

public:

	//�R���X�g���N�^
	TurnCircle(GameObject * parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

};

