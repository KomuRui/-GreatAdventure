#include "HomeScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Scene/HomeScene/HomeStage.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
HomeScene::HomeScene(GameObject* parent)
	: GameObject(parent, "HomeScene"), hAudio_(-1)
{
}

//デストラクタ
HomeScene::~HomeScene()
{
	Audio::Stop(hAudio_);
}

//初期化
void HomeScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<HomeStage>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/Home/Home.wav");
	assert(hAudio_ >= ZERO);

	//音
	//Audio::PlayLoop(hAudio_);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void HomeScene::Update()
{
}

//描画
void HomeScene::Draw()
{
}

//開放
void HomeScene::Release()
{
}

void HomeScene::StartUpdate()
{
}
