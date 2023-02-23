#include "PrincessIconButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../IconSelectUI.h"

//定数
namespace
{
	//このアイコンのモデルパス
	static const std::string ICON_MODEL_PATH = "Stage/UserSelect/Model/PrincessIconModel.fbx"; 

	//文字
	static const wchar_t DRAW_TEXT[] = L"ピ-ちゃん";  //描画する文字
	static const int DRAW_X = 700;                    //描画位置X
	static const int DRAW_Y = 850;                    //描画位置Y
}

//コンストラクタ
PrincessIconButton::PrincessIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1), NameText(new Text)
{}

//初期化
void PrincessIconButton::ChildInitialize()
{
	//初期化
	NameText->Initialize();

	//セレクト画像の番号取得
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//ロード
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/PrincessIcon_Select.png"));
}

//ボタンが押されたら何するか
void PrincessIconButton::IsButtonPush()
{
	//親に押されたことを報告
	((IconSelectUI*)GetParent())->ChangeEasingMove(ICON_MODEL_PATH);
}

//描画
void PrincessIconButton::ChildDraw()
{
	//最後まで描画されたら最初から描画し直す
	if(isSelect_)NameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//ボタンが選択された瞬間に何をするか
void PrincessIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void PrincessIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
