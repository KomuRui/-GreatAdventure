#include "BossEnemyMovie.h"

//�R���X�g���N�^
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie")
{}

//������
void BossEnemyMovie::ChildInitialize()
{
	/////////////////���邳�ݒ�/////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void BossEnemyMovie::ChildStartUpdate()
{}

//�X�V
void BossEnemyMovie::ChildUpdate()
{
	

}