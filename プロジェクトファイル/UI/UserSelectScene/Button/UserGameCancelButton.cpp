#include "UserGameCancelButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../../../Engine/ResourceManager/Time.h"
#include "../../../Engine/ResourceManager/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../../../OtherObject/SelectPlanetController.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "UserGameStartButton.h"
#include "../NewFileUI.h"

//定数
namespace
{
	static const float EASING_MOVE_TIME = 2.0f; //イージングの移動にかかる時間
}

//コンストラクタ
UserGameCancelButton::UserGameCancelButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void UserGameCancelButton::ChildInitialize()
{
	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(easingAfterPos_, XMFLOAT3(-0.5,-0.5,ZERO));
	ARGUMENT_INITIALIZE(easingBeforePos_, XMFLOAT3(easingAfterPos_.x, easingAfterPos_.y - 1.0f, easingAfterPos_.z));
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, easingBeforePos_, easingAfterPos_, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////画像の初期設定////////////////////////////////////
		
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//更新
void UserGameCancelButton::ChildButtonUpdate()
{
	//移動
	pEasingMove_->Move();
}

//ボタンが押されたら何するか
void UserGameCancelButton::IsButtonPush()
{
	//選択中に戻る状態にセット
	SelectPlanetController::SetStatus(SelectPlanetStatus::BackSelecting);

	//リセットする
	ButtonManager::Reset();

	//イージングリセット
	((UserGameStartButton*)FindObject("UserGameStartButton"))->ResetEasing();
	pEasingMove_->Reset(&transform_.position_, easingAfterPos_, easingBeforePos_, EASING_MOVE_TIME, Easing::OutQuart);
}

//ボタンが選択された瞬間に何をするか
void UserGameCancelButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void UserGameCancelButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }