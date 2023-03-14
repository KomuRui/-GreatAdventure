#include "PigIconButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../IconSelectUI.h"

//定数
namespace
{
	//このアイコンのモデルパス
	static const std::string ICON_MODEL_PATH = "Stage/UserSelect/Model/PigIconModel.fbx";

	//文字
	static const wchar_t DRAW_TEXT[] = L"ピクモン";   //描画する文字
	static const int DRAW_X = 750;                    //描画位置X
	static const int DRAW_Y = 850;                    //描画位置Y
}

//コンストラクタ
PigIconButton::PigIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1), NameText(new Text)
{}

//初期化
void PigIconButton::ChildInitialize()
{
	//初期化
	NameText->Initialize();

	//押すの許可しない
	ARGUMENT_INITIALIZE(isPushOk_, false);

	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/PigIcon_Select.png"));
}

//更新
void PigIconButton::ChildButtonUpdate()
{
	//ボタン押すの許可するか取得
	ARGUMENT_INITIALIZE(isPushOk_, ((IconSelectUI*)GetParent())->IsButtonPushOk());
}

//描画
void PigIconButton::ChildDraw()
{
	//最後まで描画されたら最初から描画し直す
	if (isSelect_)NameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//ボタンが押されたら何するか
void PigIconButton::IsButtonPush()
{
	//親に押されたことを報告
	((IconSelectUI*)GetParent())->ChangeEasingMove(ICON_MODEL_PATH);
}

//ボタンが選択された瞬間に何をするか
void PigIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void PigIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }