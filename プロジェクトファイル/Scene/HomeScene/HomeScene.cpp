#include "HomeScene.h"
#include "../../Engine/SceneManager.h"
#include "../../Player.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Scene/HomeScene/HomeStage.h"
#include "../../Engine/Camera.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
HomeScene::HomeScene(GameObject* parent)
	: GameObject(parent, "HomeScene")
{

}

//初期化
void HomeScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<HomeStage>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	GameManager::SetStatus(FADE_IN);
}

//更新
void HomeScene::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_WORLD1);
	}
}

//描画
void HomeScene::Draw()
{
}

//開放
void HomeScene::Release()
{
}

void HomeScene::StartUpdate()
{
}
