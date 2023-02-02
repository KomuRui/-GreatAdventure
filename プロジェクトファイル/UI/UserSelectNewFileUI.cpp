#include "UserSelectNewFileUI.h"
#include "../Engine/CreateStage.h"
#include "../Engine/Easing.h"

//コンストラクタ
UserSelectNewFileUI::UserSelectNewFileUI(GameObject* parent)
	: GameObject(parent, "UserSelectNewFileUI"), isPush_(false)
{
}

//初期化
void UserSelectNewFileUI::Initialize()
{
	////////////////////////////////transform////////////////////////////////////

	transform_.position_.x = 2;
	Time::UnLock();

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
	if(isPush_)
		transform_.position_ = VectorToFloat3(XMVectorLerp(XMVectorSet(0, 0, 0, 0), XMVectorSet(-2, 0, 0, 0), Easing::InQuart(Time::GetTimef() / 2.0f)));
	else
	    transform_.position_ = VectorToFloat3(XMVectorLerp(XMVectorSet(2, 0, 0, 0),XMVectorSet(0,0,0,0),Easing::OutQuart(Time::GetTimef() / 2.0f)));
}

//描画
void UserSelectNewFileUI::Draw()
{

}

//解放
void UserSelectNewFileUI::Release()
{
}
