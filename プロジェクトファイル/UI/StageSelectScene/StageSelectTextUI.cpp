#include "StageSelectTextUI.h"

//定数
namespace
{
	static const wchar_t DRAW_TEXT[] = L"ステ-ジセレクト";   //描画する文字
	static const int DRAW_X = 100;                           //描画位置X
	static const int DRAW_Y = 100;                           //描画位置Y
}

//コンストラクタ
StageSelectTextUI::StageSelectTextUI(GameObject* parent)
	: GameObject(parent, "StageSelectTextUI"), sceneNameText(new Text)
{
}

//初期化
void StageSelectTextUI::Initialize()
{
	//初期化
	sceneNameText->Initialize();
}

//更新の前に一度だけ呼ばれる
void StageSelectTextUI::StartUpdate()
{
}

//更新
void StageSelectTextUI::Update()
{
}

//描画
void StageSelectTextUI::Draw()
{
	//最後まで描画されたら最初から描画し直す
	sceneNameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//解放
void StageSelectTextUI::Release()
{
}
