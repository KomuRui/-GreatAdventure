#include "WorldScene1.h"
#include "../../../Manager/SceneManager/SceneManager.h"
#include "../../../Player/Player3D.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Engine/ResourceManager/Fade.h"
#include "../../../Engine/ResourceManager/Audio.h"
#include "../../../Gimmick/Warp.h"
#include "WorldStage1.h"

//コンストラクタ
WorldScene1::WorldScene1(GameObject* parent)
	: GameObject(parent, "WorldScene1"), hAudio_(-1)
{
}

//デストラクタ
WorldScene1::~WorldScene1()
{
	Audio::Stop(hAudio_);
}

//初期化
void WorldScene1::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<WorldStage1>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/World1/World1.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void WorldScene1::Update()
{
}

//描画
void WorldScene1::Draw()
{
}

//開放
void WorldScene1::Release()
{
}

void WorldScene1::StartUpdate()
{
}
