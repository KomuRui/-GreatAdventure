#include "Button.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
Button::Button(GameObject* parent)
	: GameObject(parent, "Button"), controllerSelect(false), hPict_(-1), pfadeButton(new Fade)
{
}


Button::Button(GameObject* parent,std::string name)
	: GameObject(parent, name), controllerSelect(false), hPict_(-1), pfadeButton(new Fade)
{
}

//初期化
void Button::Initialize()
{
	///////////////画像データのロード///////////////////
	hPict_ = Image::Load(fileNamePas);
	assert(hPict_ >= 0);
}

//更新
void Button::Update()
{
	//ボタンが選ばれている時に何をするか
	IsButtonSelect();

	//自信が選ばれていてかつ任意のボタンが押されたら
	if (controllerSelect && (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN)))
	{
		//ボタンが押された時の処理
		IsButtonPush();
	}
}

//描画
void Button::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Button::Release()
{
}

void Button::StartUpdate()
{
}

//ボタンが選ばれている時にすること(デフォルトフェードする)
void Button::IsButtonSelect()
{
	if (controllerSelect)
	{
		pfadeButton->FadeInOut(hPict_, 2.0f);
	}
	else if (!controllerSelect)
	{
		if (Image::GetAlpha(hPict_) != 255)
			Image::SetAlpha(hPict_, 255);
	}
}
