#include "TutorialScene2.h"
#include "../Engine/SceneManager.h"
#include "../Player.h"
#include "../TutorialScene/TutorialStage2.h"
#include "../Engine/GameManager.h"

//コンストラクタ
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2")
{

}

//初期化
void TutorialScene2::Initialize()
{
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));
	Instantiate<Player>(this);
}

//更新
void TutorialScene2::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_TUTORIAL1);
	}
}

//描画
void TutorialScene2::Draw()
{
}

//開放
void TutorialScene2::Release()
{
}

void TutorialScene2::StartUpdate()
{
}
