#include "UserGameStartButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../../../Engine/Time.h"
#include "../../../Engine/Easing.h"
#include "../NewFileUI.h"

//コンストラクタ
UserGameStartButton::UserGameStartButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void UserGameStartButton::ChildInitialize()
{
	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//ボタンが押されたら何するか
void UserGameStartButton::IsButtonPush()
{
}

//ボタンが選択された瞬間に何をするか
void UserGameStartButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void UserGameStartButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }