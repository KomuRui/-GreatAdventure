#include "BossEnemyMovie.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"

//�R���X�g���N�^
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie"), addScaleValue_(ZERO)
{}

//������
void BossEnemyMovie::ChildInitialize()
{
	//�R�C����1�z���������ɉ��Z����l��ݒ�
	ARGUMENT_INITIALIZE(addScaleValue_, 2.0f / CoinManager::GetCoinNum());

	//���邳�ݒ�
	Model::SetBrightness(hModel_, 1.0f);
}

//�X�V
void BossEnemyMovie::ChildUpdate()
{
	//Player�̕�������
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);
}

//�g�傷��
void BossEnemyMovie::AddScale()
{
	ARGUMENT_INITIALIZE(transform_.scale_,Float3Add(transform_.scale_, { addScaleValue_,addScaleValue_,addScaleValue_ }));
}