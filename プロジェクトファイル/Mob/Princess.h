#pragma once
#include "../Mob/Mob.h"
#include "../UI/TalkImage.h"

/// <summary>
/// �Ō�̃V�[���̃v�����Z�X
/// </summary>
class Princess : public Mob
{
	//�\���������摜�̃N���X��ۑ����Ă����p
	TalkImage* pTalkImage_;

public:

	//�R���X�g���N�^
	Princess(GameObject* parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

};

