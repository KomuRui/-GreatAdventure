#include "StageSelectScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Scene/StageSelectScene/StageSelectStage.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"), hAudio_(-1)
{
}

//デストラクタ
StageSelectScene::~StageSelectScene()
{
	Audio::Stop(hAudio_);
}

//初期化
void StageSelectScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<StageSelectStage>(this));

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/Home/Home.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void StageSelectScene::Update()
{
}

//描画
void StageSelectScene::Draw()
{
}
