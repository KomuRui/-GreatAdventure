#include "NewFileOKButton.h"
#include "../../Engine/Global.h"
#include "../../Engine/Image.h"

//コンストラクタ
NewFileOKButton::NewFileOKButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{

	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hNotSelectPict_, Image::Load("Image/UserSelect/Cancel_Select.png"));
}

//ボタンが押されたら何するか
void NewFileOKButton::IsButtonPush()
{

}

//ボタンが選択された瞬間に何をするか
void NewFileOKButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void NewFileOKButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }