#include "TutorialScene2.h"
#include "../../Engine/SceneManager.h"
#include "../../Player.h"
#include "../../Scene/TutorialScene/TutorialStage2.h"
#include "../../Engine/GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/Camera.h"

//コンストラクタ
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2")
{

}

//初期化
void TutorialScene2::Initialize()
{
	//これから使うステージのポインタをGameManagerにセット
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//ワープのポジションと移動先の設定
	pWarp->SetPosition(GameManager::GetpPlayer()->GetPosition());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetNumber(2);

	GameManager::SetStatus(FADE_IN);
}

//更新
void TutorialScene2::Update()
{
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_HOME);
	}
}

//描画
void TutorialScene2::Draw()
{
}

//開放
void TutorialScene2::Release()
{
}

void TutorialScene2::StartUpdate()
{
}
