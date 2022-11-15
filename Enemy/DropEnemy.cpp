#include "DropEnemy.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
DropEnemy::DropEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name)
{
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void DropEnemy::EnemyChildStartUpdate()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hHedModel_ = Model::Load("Enemy/Model/DropEnemyHed.fbx");
	assert(hHedModel_ >= 0);

	///////////////�A�j���[�V����///////////////////

	//�J�n
	Model::SetAnimFrame(hModel_, 1, 60, 3);
}

//�X�V
void DropEnemy::EnemyChildUpdate()
{
	Model::SetSpeculer(hHedModel_, XMFLOAT4(((rand() % 11)  / 10) + 0.2, ((rand() % 11) / 10) + 0.2, ((rand() % 11) / 10) + 0.2, 1.0f));
}

//�`��
void DropEnemy::EnemyChildDraw()
{
	Model::SetTransform(hHedModel_, transform_);
	Model::Draw(hHedModel_);
}
