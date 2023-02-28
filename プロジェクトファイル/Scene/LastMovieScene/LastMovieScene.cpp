#include "LastMovieScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"

//コンストラクタ
LastMovieScene::LastMovieScene(GameObject* parent)
	: GameObject(parent, "LastMovieScene")
{

}

//初期化
void LastMovieScene::Initialize()
{
	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void LastMovieScene::Update()
{
}

//描画
void LastMovieScene::Draw()
{
}

//開放
void LastMovieScene::Release()
{
}

void LastMovieScene::StartUpdate()
{
}