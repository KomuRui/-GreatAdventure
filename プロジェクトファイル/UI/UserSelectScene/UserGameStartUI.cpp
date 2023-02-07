#include "UserGameStartUI.h"
#include "../../Engine/CreateStage.h"
#include "../../Engine/Easing.h"
#include "../../Engine/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "IconSelectUI.h"

//コンストラクタ
UserGameStartUI::UserGameStartUI(GameObject* parent)
	: GameObject(parent, "UserGameStartUI"), pCreateStage_(new CreateStage)
{}

//初期化
void UserGameStartUI::Initialize()
{
	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserGameStartUI.txt");
}


//更新
void UserGameStartUI::Update()
{
}
