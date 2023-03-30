#include "ImageBase.h"
#include "../Engine/ResourceManager/Image.h"

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
	ARGUMENT_INITIALIZE(pathName_, ModelNamePath_);
	assert(hPict_ >= ZERO);

	//継承用の初期化
	ChildInitialize();
}

//更新の前に一度だけ呼ばれる
void ImageBase::StartUpdate()
{
	//継承用のStart更新
	ChildStartUpdate();
}

//更新
void ImageBase::Update()
{
	//継承用の更新
	ChildUpdate();
}

//描画
void ImageBase::Draw()
{
	//画像表示
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	//継承用の描画
	ChildDraw();
}

//解放
void ImageBase::Release()
{
}
