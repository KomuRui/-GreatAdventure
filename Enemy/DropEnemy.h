#pragma once
#include "Enemy.h"

class DropEnemy : public Enemy
{
	//���̃��f��
	int hHedModel_; 

public:

	//�R���X�g���N�^
	DropEnemy(GameObject* parent, std::string modelPath, std::string name);

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void EnemyChildStartUpdate() override;

	//�X�V
	void EnemyChildUpdate() override;

	//�`��
	void EnemyChildDraw() override;
};

