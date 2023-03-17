#include "SaveButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//コンストラクタ
SaveButton::SaveButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1)
{}

//初期化
void SaveButton::ChildInitialize()
{
	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/Save_Select.png"));
}

//ボタンが押されたら何するか
void SaveButton::IsButtonPush()
{
}

//ボタンが選択された瞬間に何をするか
void SaveButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void SaveButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
