#include "TitleStartImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"

//定数
namespace
{
	const XMFLOAT3 BEFORE_SCALE = { 1.0,1.0,1.0 }; //変更前の拡大率
	const XMFLOAT3 AFTER_SCALE = { 1.1,1.1,1.1 };  //変更後の拡大率
}

//コンストラクタ
TitleStartImage::TitleStartImage(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), ModelNamePath_(modelPath), hPict_Default_(-1), hPict_A_Select_(-1), hPict_RT_Select_(-1), hPict_All_Select_(-1)
{
}

//初期化
void TitleStartImage::Initialize()
{
	///////////////画像データのロード///////////////////

	//デフォルト
	hPict_Default_ = Image::Load(ModelNamePath_);
	assert(hPict_Default_ >= ZERO);

	//Aが押されてるとき
	hPict_A_Select_ = Image::Load("Image/Title/Start_A_Select.png");
	assert(hPict_A_Select_ >= ZERO);

	//RTが押されてるとき
	hPict_RT_Select_ = Image::Load("Image/Title/Start_RT_Select.png");
	assert(hPict_RT_Select_ >= ZERO);

	//すべてが押されてるとき
	hPict_All_Select_ = Image::Load("Image/Title/Start_ALL_Select.png");
	assert(hPict_All_Select_ >= ZERO);
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
		Image::SetTransform(hPict_All_Select_, transform_);
		Image::Draw(hPict_All_Select_);
	}
	//もしAが押されているなら
	else if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		Image::SetTransform(hPict_A_Select_, transform_);
		Image::Draw(hPict_A_Select_);
	}
	//もしRTが押されているなら
	else if (Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_RT_Select_, transform_);
		Image::Draw(hPict_RT_Select_);
	}
	//もし何も押されていないなら
	else
	{
		Image::SetTransform(hPict_Default_, transform_);
		Image::Draw(hPict_Default_);
	}
	
}

//解放
void TitleStartImage::Release()
{
}
