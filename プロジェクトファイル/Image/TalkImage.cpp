#include "TalkImage.h"
#include "../Engine/Image.h"

//コンストラクタ
TalkImage::TalkImage(GameObject* parent)
	: GameObject(parent, "TalkImage"), hBasePict_(-1),hCharaPict_(-1), pText_(new Text)
{
}

//初期化
void TalkImage::Initialize()
{
	///////////////文字のロード///////////////////

	//初期化
	pText_->Initialize(1.0f);

	///////////////画像データのロード///////////////////

	hBasePict_ = Image::Load("Image/Text/Talk.png");
	assert(hBasePict_ >= ZERO);

	hCharaPict_ = Image::Load("Image/MainMob/MainMobImage.png");
	assert(hCharaPict_ >= ZERO);

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

	//文字描画
	pText_->SlowlyDraw(1000, 840, "0101010101", 0.8);
}

//解放
void TalkImage::Release()
{
}
