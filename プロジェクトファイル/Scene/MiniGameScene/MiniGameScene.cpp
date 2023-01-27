#include "MiniGameScene.h"
#include "MiniGameStage.h"
#include "../../Engine/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Engine/Camera.h"
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
	GameManager::SetpPlayer(Instantiate<Player3D>(this));

	//オブジェクトセット用
	Instantiate<MiniGameSetObject>(this);

	//フェードイン
	GameManager::SetStatus(FADE_IN);
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
