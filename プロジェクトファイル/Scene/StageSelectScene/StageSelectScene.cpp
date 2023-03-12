#include "StageSelectScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Scene/StageSelectScene/StageSelectStage.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene")
{

}

//初期化
void StageSelectScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<StageSelectStage>(this));

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

//開放
void StageSelectScene::Release()
{
}

void StageSelectScene::StartUpdate()
{
}
