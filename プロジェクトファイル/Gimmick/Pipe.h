#pragma once
#include "../Mob/Mob.h"

/// <summary>
/// �~�j�Q�[���ɓo�ꂷ��M�~�b�N�̃p�C�v
/// </summary>
class Pipe : public Mob
{

public:

	//�R���X�g���N�^
	Pipe(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;
};

