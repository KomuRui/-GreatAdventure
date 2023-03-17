#include "PauseBackButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//コンストラクタ
PauseBackButton::PauseBackButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1),hSelectPict2_(-1)
{}

//初期化
void PauseBackButton::ChildInitialize()
{
	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/Back_Select.png"));
	ARGUMENT_INITIALIZE(hSelectPict2_, Image::Load("Image/Pause/Back_Explain.png"));
}

//描画
void PauseBackButton::ChildDraw()
{
	//選択されているのなら
	if (isSelect_)
	{
		Transform t;
		Image::SetTransform(hSelectPict2_, t);
		Image::Draw(hSelectPict2_);
	}
}

//ボタンが押されたら何するか
void PauseBackButton::IsButtonPush()
{
}

//ボタンが選択された瞬間に何をするか
void PauseBackButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void PauseBackButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
