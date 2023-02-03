#include "UserSelectSceneUI.h"

//定数
namespace
{
	static const wchar_t DRAW_TEXT[] = L"プレイヤ-セレクト"; //描画する文字
	static const int DRAW_X = 100;                           //描画位置X
	static const int DRAW_Y = 100;                           //描画位置Y
}

//コンストラクタ
UserSelectSceneUI::UserSelectSceneUI(GameObject* parent)
	: GameObject(parent, "UserSelectSceneUI"), sceneNameText(new Text)
{
}

//初期化
void UserSelectSceneUI::Initialize()
{
	//初期化
	sceneNameText->Initialize();
}

//更新の前に一度だけ呼ばれる
void UserSelectSceneUI::StartUpdate()
{
}

//更新
void UserSelectSceneUI::Update()
{
}

//描画
void UserSelectSceneUI::Draw()
{
	//最後まで描画されたら最初から描画し直す
	sceneNameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT,0.8f);
}

//解放
void UserSelectSceneUI::Release()
{
}
