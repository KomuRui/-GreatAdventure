#include "ImageBase.h"
#include "../Engine/Image.h"

//コンストラクタ
ImageBase::ImageBase(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), hPict_(-1), ModelNamePath_(modelPath)
{
}

//初期化
void ImageBase::Initialize()
{
	///////////////画像データのロード///////////////////
	
	hPict_ = Image::Load(ModelNamePath_);
	assert(hPict_ >= 0);
}

//更新の前に一度だけ呼ばれる
void ImageBase::StartUpdate()
{
}

//更新
void ImageBase::Update()
{
}

//描画
void ImageBase::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//解放
void ImageBase::Release()
{
}
