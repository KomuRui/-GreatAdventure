#include "NewFileOkButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../NewFileUI.h"

//コンストラクタ
NewFileOkButton::NewFileOkButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void NewFileOkButton::ChildInitialize()
{
	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/Ok_Select.png"));
}

//ボタンが押されたら何するか
void NewFileOkButton::IsButtonPush()
{
	//親に押されたことを報告
	((NewFileUI*)GetParent())->ChangeEasingMove();
}

//ボタンが選択された瞬間に何をするか
void NewFileOkButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void NewFileOkButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }