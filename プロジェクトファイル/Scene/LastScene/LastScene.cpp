#include "LastScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"

//�R���X�g���N�^
LastScene::LastScene(GameObject* parent)
	: GameObject(parent, "LastScene")
{

}

//������
void LastScene::Initialize()
{
	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
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