#include "LastScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "LastStage.h"
#include "../../Player/Player3D.h"
#include "../../OtherObject/ShootingStarCreate.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"
#include "../../Engine/ResourceManager/Audio.h"

//コンストラクタ
LastScene::LastScene(GameObject* parent)
	: GameObject(parent, "LastScene"), hAudio_(-1)
{
}

//デストラクタ
LastScene::~LastScene()
{
	Audio::Stop(hAudio_);
}

//初期化
void LastScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<LastStage>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));

	//流れ星生成
	Instantiate<ShootingStarCreate>(this);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/Last/Last.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);
}

//更新
void LastScene::Update()
{
}

//描画
void LastScene::Draw()
{
}

//開放
void LastScene::Release()
{
}

void LastScene::StartUpdate()
{
}