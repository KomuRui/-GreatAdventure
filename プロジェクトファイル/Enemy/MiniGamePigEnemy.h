#pragma once
#include "PigEnemy.h"

/// <summary>
/// �~�j�Q�[���p�̓؂̓G
/// </summary>
class MiniGamePigEnemy : public PigEnemy
{

public:

	//�R���X�g���N�^
	MiniGamePigEnemy(GameObject* parent);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void ChildPigEnemyStartUpdate() override;

	//�X�V
	void ChildPigEnemyUpdate() override;

};

