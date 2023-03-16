#include "TutorialScene2.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Scene/TutorialScene/TutorialStage2.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"

//コンストラクタ
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2"), hAudio_(-1)
{

}

//デストラクタ
TutorialScene2::~TutorialScene2()
{
	Audio::Stop(hAudio_);
}


//初期化
void TutorialScene2::Initialize()
{
	//これから使うステージのポインタをGameManagerにセット
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);

	//音ロード
	hAudio_ = Audio::Load("Audio/BGM/Tutorial/TutorialScene.wav");
	assert(hAudio_ >= ZERO);

	//音
	Audio::PlayLoop(hAudio_);
}

//更新
void TutorialScene2::Update()
{
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
