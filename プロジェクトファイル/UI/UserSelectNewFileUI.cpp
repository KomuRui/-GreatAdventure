#include "UserSelectNewFileUI.h"
#include "../Engine/CreateStage.h"

//コンストラクタ
UserSelectNewFileUI::UserSelectNewFileUI(GameObject* parent)
	: GameObject(parent, "UserSelectNewFileUI")
{
}

//初期化
void UserSelectNewFileUI::Initialize()
{
	////////////////////////////////transform////////////////////////////////////

	transform_.position_.x = -10;

	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_ = new CreateStage;
	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserSelectNewFileUI.txt");
}

//更新の前に一度だけ呼ばれる
void UserSelectNewFileUI::StartUpdate()
{
}

//更新
void UserSelectNewFileUI::Update()
{
}

//描画
void UserSelectNewFileUI::Draw()
{

}

//解放
void UserSelectNewFileUI::Release()
{
}
