#include "EndRolesScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../UI/EndRolesScene/EndRoles.h"


//コンストラクタ
EndRolesScene::EndRolesScene(GameObject* parent)
	: GameObject(parent, "EndRolesScene")
{

}

//初期化
void EndRolesScene::Initialize()
{
	//エンドロール表示
	Instantiate<EndRoles>(this,"Image/EndRole/EndRoleImage.png","EndRoles");

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void EndRolesScene::Update()
{
}

//描画
void EndRolesScene::Draw()
{
}

//開放
void EndRolesScene::Release()
{
}

void EndRolesScene::StartUpdate()
{
}