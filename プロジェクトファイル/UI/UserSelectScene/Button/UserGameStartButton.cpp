#include "UserGameStartButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../../../Engine/Time.h"
#include "../../../Engine/Easing.h"
#include "../../../Engine/Component/EasingMove.h"
#include "../NewFileUI.h"

//定数
namespace
{
	static const float EASING_MOVE_TIME = 2.0f; //イージングの移動にかかる時間
}

//コンストラクタ
UserGameStartButton::UserGameStartButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void UserGameStartButton::ChildInitialize()
{
	////////////////////////////////イージングの初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(easingAfterPos_, transform_.position_);
	ARGUMENT_INITIALIZE(easingBeforePos_,XMFLOAT3(transform_.position_.x,transform_.position_.y - 1.0f,transform_.position_.z));
	ARGUMENT_INITIALIZE(pEasingMove_, new EasingMove(&transform_.position_, easingBeforePos_, easingAfterPos_, EASING_MOVE_TIME, Easing::OutQuart))

	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//更新
void UserGameStartButton::ChildButtonUpdate()
{
	//移動
	pEasingMove_->Move();
}

//ボタンが押されたら何するか
void UserGameStartButton::IsButtonPush()
{
}

//ボタンが選択された瞬間に何をするか
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }