#pragma once
#include "../Mob/Mob.h"

/// <summary>
/// ����p�̃{�X�̓G
/// </summary>
class BossEnemyMovie : public Mob
{
	//���Z����l
	float addScaleValue_;

public:

	//�R���X�g���N�^
	BossEnemyMovie(GameObject*parent, std::string modelPath, std::string name);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	/////////////////////�֐�//////////////////////

	//�g�傷��
	void AddScale();
};

