#include "PigEnemy.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name)
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void PigEnemy::EnemyChildStartUpdate()
{
	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, 1, 60, 3);
}