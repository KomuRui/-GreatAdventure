#include "MiniGameScene.h"
#include "MiniGameStage.h"
#include "../../Engine/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
#include "../../MiniGame/MiniGameSetObject.h"

//�R���X�g���N�^
MiniGameScene::MiniGameScene(GameObject* parent)
	: GameObject(parent, "MiniGameScene")
{

}

//������
void MiniGameScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<MiniGameStage>(this));

	//Player�\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpPlayer(Instantiate<Player3D>(this));

	//�I�u�W�F�N�g�Z�b�g�p
	Instantiate<MiniGameSetObject>(this);

	//�t�F�[�h�C��
	GameManager::SetStatus(FADE_IN);
}

//�X�V
void MiniGameScene::Update()
{
}

//�`��
void MiniGameScene::Draw()
{
}

//�J��
void MiniGameScene::Release()
{
}

void MiniGameScene::StartUpdate()
{
}
