#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Camera.h"
#include "TutorialStage.h"
#include "../Player.h"
#include "../Stage.h"
#include "../Engine/ImGuiSet.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{

}

//初期化
void TutorialScene::Initialize()
{
	Instantiate<TutorialStage>(this);
	Instantiate<Player>(this);
	ImGuiSet *a = Instantiate<ImGuiSet>(this);

	a->CreateStage("TutorialStage1.txt");

	///////////////画像データのロード///////////////////


	///////////////transform///////////////////


	///////////////カメラ///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));

}

//更新
void TutorialScene::Update()
{
}

//描画
void TutorialScene::Draw()
{
}

//開放
void TutorialScene::Release()
{
}

void TutorialScene::StartUpdate()
{
}
