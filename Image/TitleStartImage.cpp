#include "TitleStartImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"

//コンストラクタ
TitleStartImage::TitleStartImage(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), ModelNamePath_(modelPath)
{
	for (int i = ZERO; i < MAX_IMAGE_TYPE; i++)
	{
		//初期化
		ARGUMENT_INITIALIZE(hPict_[i], -1);
	}
}

//初期化
void TitleStartImage::Initialize()
{
	///////////////画像データのロード///////////////////

	//デフォルト
	hPict_[Default] = Image::Load(ModelNamePath_);
	assert(hPict_ >= ZERO);

	//Aが押されてるとき
	hPict_[A_Select] = Image::Load("Image/Title/Start_A_Select.png");
	assert(hPict_ >= ZERO);

	//RTが押されてるとき
	hPict_[RT_Select] = Image::Load("Image/Title/Start_RT_Select.png");
	assert(hPict_ >= ZERO);

	//すべてが押されてるとき
	hPict_[All_Select] = Image::Load("Image/Title/Start_ALL_Select.png");
	assert(hPict_ >= ZERO);
}

//更新の前に一度だけ呼ばれる
void TitleStartImage::StartUpdate()
{
}

//更新
void TitleStartImage::Update()
{
	//もしAかRTが押されてるなら
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) || Input::GetPadTrrigerR())
	{
		ARGUMENT_INITIALIZE(transform_.scale_, AFTER_SCALE);
	}
	else
		ARGUMENT_INITIALIZE(transform_.scale_, BEFORE_SCALE);
}

//描画
void TitleStartImage::Draw()
{
	//もしAとRTが同時押しされてるなら
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_[All_Select], transform_);
		Image::Draw(hPict_[All_Select]);
	}
	//もしAが押されているなら
	else if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		Image::SetTransform(hPict_[A_Select], transform_);
		Image::Draw(hPict_[A_Select]);
	}
	//もしRTが押されているなら
	else if (Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_[RT_Select], transform_);
		Image::Draw(hPict_[RT_Select]);
	}
	//もし何も押されていないなら
	else
	{
		Image::SetTransform(hPict_[Default], transform_);
		Image::Draw(hPict_[Default]);
	}
	
}

//解放
void TitleStartImage::Release()
{
}
