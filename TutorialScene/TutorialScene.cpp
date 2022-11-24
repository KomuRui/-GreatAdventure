#include "TutorialScene.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Camera.h"
#include "TutorialStage.h"
#include "../Player.h"
#include "../Gimmick/Signboard.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{

}

//初期化
void TutorialScene::Initialize()
{
	Instantiate<TutorialStage>(this);
	Instantiate<Signboard>(this,"Image/Tutorial/MoveOperate.png");
	Instantiate<Player>(this);
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
