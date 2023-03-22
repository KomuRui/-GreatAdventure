#include "MiniGameScene.h"
#include "MiniGameStage.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/PlayerMiniGame.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../MiniGame/MiniGameSetObject.h"
#include "../../Engine/ResourceManager/Audio.h"

//コンストラクタ
MiniGameScene::MiniGameScene(GameObject* parent)
	: GameObject(parent, "MiniGameScene"), hAudio_(-1)
{
}

//デストラクタ
MiniGameScene::~MiniGameScene()
{
	Audio::Stop(hAudio_);
}

//初期化
void MiniGameScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<MiniGameStage>(this));

	//Player表示(これから使うステージのポインタをGameManagerにセット)
	GameManager::SetpPlayer(Instantiate<PlayerMiniGame>(this));

	//オブジェクトセット用
	Instantiate<MiniGameSetObject>(this);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/MiniGame/MiniGame.wav");
	assert(hAudio_ >= ZERO);

	//音
	//Audio::PlayLoop(hAudio_);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void MiniGameScene::Update()
{
}

//描画
void MiniGameScene::Draw()
{
}

//開放
void MiniGameScene::Release()
{
}

void MiniGameScene::StartUpdate()
{
}
