#include "PrincessIconButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../NewFileUI.h"

//コンストラクタ
PrincessIconButton::PrincessIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void PrincessIconButton::ChildInitialize()
{
	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/PrincessIcon_Select.png"));
}

//ボタンが押されたら何するか
void PrincessIconButton::IsButtonPush()
{
	//親に押されたことを報告
	((NewFileUI*)GetParent())->ChangeEasingMove();
}

//ボタンが選択された瞬間に何をするか
void PrincessIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void PrincessIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }