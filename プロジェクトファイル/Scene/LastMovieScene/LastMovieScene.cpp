#include "LastMovieScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"

//�R���X�g���N�^
LastMovieScene::LastMovieScene(GameObject* parent)
	: GameObject(parent, "LastMovieScene")
{

}

//������
void LastMovieScene::Initialize()
{
	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void LastMovieScene::Update()
{
}

//�`��
void LastMovieScene::Draw()
{
}

//�J��
void LastMovieScene::Release()
{
}

void LastMovieScene::StartUpdate()
{
}