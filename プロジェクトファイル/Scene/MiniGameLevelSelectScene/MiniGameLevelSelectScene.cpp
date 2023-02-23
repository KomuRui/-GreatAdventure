#include "MiniGameLevelSelectScene.h"
#include "MiniGameLevelSelectStage.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Gimmick/Warp.h"

//コンストラクタ
MiniGameLevelSelectScene::MiniGameLevelSelectScene(GameObject* parent)
	: GameObject(parent, "MiniGameLevelSelectScene")
{

}

//初期化
void MiniGameLevelSelectScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<MiniGameLevelSelectStage>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void MiniGameLevelSelectScene::Update()
{
}

//描画
void MiniGameLevelSelectScene::Draw()
{
}

//開放
void MiniGameLevelSelectScene::Release()
{
}

void MiniGameLevelSelectScene::StartUpdate()
{
}
