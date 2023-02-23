#include "MiniGameScene.h"
#include "MiniGameStage.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/PlayerMiniGame.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../MiniGame/MiniGameSetObject.h"

//コンストラクタ
MiniGameScene::MiniGameScene(GameObject* parent)
	: GameObject(parent, "MiniGameScene")
{

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
