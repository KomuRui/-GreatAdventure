#include "TalkImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"

//コンストラクタ
TalkImage::TalkImage(GameObject* parent)
	: GameObject(parent, "TalkImage"), hBasePict_(-1),hCharaPict_(-1), hNextPict_(-1),pText_(new Text)
{
}

//初期化
void TalkImage::Initialize()
{
	///////////////文字のロード///////////////////

	//初期化
	pText_->Initialize(0.1f);

	///////////////画像データのロード///////////////////

	hBasePict_ = Image::Load("Image/Text/Talk.png");
	assert(hBasePict_ >= ZERO);

	hCharaPict_ = Image::Load("Image/MainMob/MainMobImage.png");
	assert(hCharaPict_ >= ZERO);

	hNextPict_ = Image::Load("Image/Text/Next.png");
	assert(hNextPict_ >= ZERO);

	/////////////////////////各Transform/////////////////////////

	//ベース
	ARGUMENT_INITIALIZE(tBase_.position_.x, GetPrivateProfilefloat("POSITION", "BaseX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.y, GetPrivateProfilefloat("POSITION", "BaseY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.z,1.0f);

	ARGUMENT_INITIALIZE(tBase_.scale_.x, GetPrivateProfilefloat("SCALE", "BaseX", "2.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.y, GetPrivateProfilefloat("SCALE", "BaseY", "0.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.z, 1.0f);

	//キャラ
	ARGUMENT_INITIALIZE(tChara_.position_.x, GetPrivateProfilefloat("POSITION", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.y, GetPrivateProfilefloat("POSITION", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tChara_.scale_.x, GetPrivateProfilefloat("SCALE", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.y, GetPrivateProfilefloat("SCALE", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.z, 1.0f);

	//Next
	ARGUMENT_INITIALIZE(tNext_.position_.x, GetPrivateProfilefloat("POSITION", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.y, GetPrivateProfilefloat("POSITION", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tNext_.scale_.x, GetPrivateProfilefloat("SCALE", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.y, GetPrivateProfilefloat("SCALE", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.z, 1.0f);
}

//更新の前に一度だけ呼ばれる
void TalkImage::StartUpdate()
{
}

//更新
void TalkImage::Update()
{
}

//描画
void TalkImage::Draw()
{
	//画像描画
	Image::SetTransform(hBasePict_, tBase_);
	Image::Draw(hBasePict_);

	Image::SetTransform(hCharaPict_, tChara_);
	Image::Draw(hCharaPict_);

	//文字描画()もし文字が最後まで描画していたら
	if (pText_->SlowlyDraw(1050, 800, L"こんにちは!,SUPER-SUTAR-GALAXY,のセカイへようこそ!", 0.3))
	{
		//Next画像を表示
		Image::SetTransform(hNextPict_, tNext_);
		Image::Draw(hNextPict_);

		//もしBボタンを押したなら
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
		{

		}
	}
}

//解放
void TalkImage::Release()
{
}
