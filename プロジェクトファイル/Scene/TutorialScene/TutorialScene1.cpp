#include "TutorialScene1.h"
#include "../../Engine/SceneManager.h"
#include "../../Player.h"
#include "../../Scene/TutorialScene/TutorialStage1.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Input.h"

//コンストラクタ
TutorialScene1::TutorialScene1(GameObject* parent)
	: GameObject(parent, "TutorialScene1")
{

}

//初期化
void TutorialScene1::Initialize()
{
	//ステージの表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpStage(Instantiate<TutorialStage1>(this));

	//Player表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpPlayer(Instantiate<Player>(this));

	//フェードイン
	GameManager::SetStatus(FADE_IN);
}

//更新
void TutorialScene1::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager"); 
		pScene->ChangeScene(SCENE_ID_TUTORIAL2);
	}
}

//描画
void TutorialScene1::Draw()
{
}

//開放
void TutorialScene1::Release()
{
}

void TutorialScene1::StartUpdate()
{
}
