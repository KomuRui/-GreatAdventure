#include "UserSelectScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/ResourceManager/CreateStage.h"
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

