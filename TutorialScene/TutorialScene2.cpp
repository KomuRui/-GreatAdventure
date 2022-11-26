#include "TutorialScene2.h"
#include "../Engine/SceneManager.h"
#include "../Player.h"
#include "../TutorialScene/TutorialStage2.h"
#include "../Engine/GameManager.h"

//�R���X�g���N�^
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2")
{

}

//������
void TutorialScene2::Initialize()
{
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));
	Instantiate<Player>(this);
}

//�X�V
void TutorialScene2::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_TUTORIAL1);
	}
}

//�`��
void TutorialScene2::Draw()
{
}

//�J��
void TutorialScene2::Release()
{
}

void TutorialScene2::StartUpdate()
{
}
