#pragma once
#include "../Mob.h"

/// <summary>
/// ����p�̃{�X�̓G
/// </summary>
class BossEnemyMovie : public Mob
{

public:

	//�R���X�g���N�^
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void ChildStartUpdate() override;

	//�X�V
	void ChildUpdate() override;
};

