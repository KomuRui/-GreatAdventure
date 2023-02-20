#include "WorldScene2.h"
#include "../../../Engine/SceneManager.h"
#include "../../../Player/Player3D.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Camera.h"
#include "../../../Gimmick/Warp.h"
#include "WorldStage2.h"

//コンストラクタ
WorldScene2::WorldScene2(GameObject* parent)
	: GameObject(parent, "WorldScene2")
{

}

//初期化
void WorldScene2::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<WorldStage2>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//フェードイン
	GameManager::SetStatus(FADE_IN);
}

//更新
void WorldScene2::Update()
{
}

//描画
void WorldScene2::Draw()
{
}

//開放
void WorldScene2::Release()
{
}

void WorldScene2::StartUpdate()
{
}
