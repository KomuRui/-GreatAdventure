#include "LastScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "LastStage.h"
#include "../../Player/Player3D.h"
#include "../../OtherObject/ShootingStarCreate.h"
#include "../../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

//コンストラクタ
LastScene::LastScene(GameObject* parent)
	: GameObject(parent, "LastScene")
{

}

//初期化
void LastScene::Initialize()
{
	//ステージの表示
	GameManager::SetpStage(Instantiate<LastStage>(this));

	//Playerとワープの表示
	GameManager::SetpPlayer(Instantiate<Player3D>(this));

	Instantiate<ShootingStarCreate>(this);

	//フェードイン
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//更新
void LastScene::Update()
{
}

//描画
void LastScene::Draw()
{
}

//開放
void LastScene::Release()
{
}

void LastScene::StartUpdate()
{
}