#include "PauseBackTitleButton.h"
#include "../../../../Engine/ResourceManager/Global.h"
#include "../../../../Engine/ResourceManager/Image.h"
#include "../../../../Manager/GameManager/GameManager.h"


//コンストラクタ
PauseBackTitleButton::PauseBackTitleButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1),hSelectPict2_(-1)
{}

//初期化
void PauseBackTitleButton::ChildInitialize()
{
	////////////////////////////////画像の初期設定////////////////////////////////////

	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/Pause/BackTitle_Select.png"));
	ARGUMENT_INITIALIZE(hSelectPict2_, Image::Load("Image/Pause/BackTitle_Explain.png"));
}

//描画
void PauseBackTitleButton::ChildDraw()
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
void PauseBackTitleButton::IsButtonPush()
{
	//ポーズ削除
	GameManager::PauseDelete();

	//ロード描画をしない
	GameManager::GetpSceneManager()->SetLoadDrawFlag(false);

	//タイトルシーンへ
	GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
}

//ボタンが選択された瞬間に何をするか
void PauseBackTitleButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//ボタンが選択解除された瞬間に何をするか
void PauseBackTitleButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
