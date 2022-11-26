#include "TutorialScene1.h"
#include "../Engine/SceneManager.h"
#include "../Player.h"
#include "../TutorialScene/TutorialStage1.h"
#include "../Engine/GameManager.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
TutorialScene1::TutorialScene1(GameObject* parent)
	: GameObject(parent, "TutorialScene1")
{

}

//������
void TutorialScene1::Initialize()
{
	GameManager::SetpStage(Instantiate<TutorialStage1>(this));
	Instantiate<Player>(this);
}

//�X�V
void TutorialScene1::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager"); 
		pScene->ChangeScene(SCENE_ID_TUTORIAL2);
	}
}

//�`��
void TutorialScene1::Draw()
{
}

//�J��
void TutorialScene1::Release()
{
}

void TutorialScene1::StartUpdate()
{
}