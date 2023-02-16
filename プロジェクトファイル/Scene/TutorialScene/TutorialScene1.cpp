#include "TutorialScene1.h"
#include "../../Engine/SceneManager.h"
#include "../../Player/Player2D.h"
#include "../../Scene/TutorialScene/TutorialStage1.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Engine/Audio.h"

//コンストラクタ
TutorialScene1::TutorialScene1(GameObject* parent)
	: GameObject(parent, "TutorialScene1"),hAudio_(-1)
{

}

//初期化
void TutorialScene1::Initialize()
{
	//ステージの表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpStage(Instantiate<TutorialStage1>(this));

	//Player表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpPlayer(Instantiate<Player2D>(this));

	//フェードイン
	GameManager::SetStatus(FADE_IN);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/TutorialScene.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);
}

//更新の前に一度だけ呼ばれる関数
void TutorialScene1::StartUpdate()
{
}

//更新
void TutorialScene1::Update()
{
	
	//テスト用
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

