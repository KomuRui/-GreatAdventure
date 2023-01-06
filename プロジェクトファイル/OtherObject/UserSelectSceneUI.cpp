#include "UserSelectSceneUI.h"

//定数
namespace
{
	static const wchar_t DRAW_TEXT[] = L"ユ-ザ-セレクト"; //描画する文字
	static const float DRAW_SPEED = 0.2f;                 //描画速度
	static const int DRAW_X = 100;                        //描画位置X
	static const int DRAW_Y = 100;                        //描画位置Y
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
	sceneNameText->SetDrawSpeed(DRAW_SPEED);
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
	if (sceneNameText->SlowlyDraw(DRAW_X, DRAW_Y, DRAW_TEXT))
		sceneNameText->SetTotalDrawNum(ZERO);
}

//解放
void UserSelectSceneUI::Release()
{
}
