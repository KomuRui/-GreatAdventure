#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "UserSelectStage.h"

//コンストラクタ
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene")
{
}

//初期化
void UserSelectScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<UserSelectStage>(this));
}

//更新の前に一度だけ呼ばれる更新
void UserSelectScene::StartUpdate()
{
}

//更新
void UserSelectScene::Update()
{
}

//描画
void UserSelectScene::Draw()
{
}

//開放
void UserSelectScene::Release()
{
}

