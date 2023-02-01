#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "UserSelectStage.h"

//�R���X�g���N�^
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene")
{
}

//������
void UserSelectScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<UserSelectStage>(this));
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void UserSelectScene::StartUpdate()
{
}

//�X�V
void UserSelectScene::Update()
{
}

//�`��
void UserSelectScene::Draw()
{
}

//�J��
void UserSelectScene::Release()
{
}

