#include "LastScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "LastStage.h"
#include "../../Player/Player3D.h"
#include "../../OtherObject/ShootingStarCreate.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//�R���X�g���N�^
LastScene::LastScene(GameObject* parent)
	: GameObject(parent, "LastScene")
{

}

//������
void LastScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<LastStage>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));

	//���ꐯ����
	Instantiate<ShootingStarCreate>(this);
}

//�X�V
void LastScene::Update()
{
}

//�`��
void LastScene::Draw()
{
}

//�J��
void LastScene::Release()
{
}

void LastScene::StartUpdate()
{
}