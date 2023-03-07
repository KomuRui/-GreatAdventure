#include "LastScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"

//コンストラクタ
LastScene::LastScene(GameObject* parent)
	: GameObject(parent, "LastScene")
{

}

//初期化
void LastScene::Initialize()
{
	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
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