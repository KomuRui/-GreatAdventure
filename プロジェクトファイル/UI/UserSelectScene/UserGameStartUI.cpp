#include "UserGameStartUI.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Engine/ResourceManager/Easing.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../OtherObject/UserInfomation.h"
#include "IconSelectUI.h"

//コンストラクタ
UserGameStartUI::UserGameStartUI(GameObject* parent)
	: GameObject(parent, "UserGameStartUI"), pCreateStage_(new CreateStage)
{}

//初期化
void UserGameStartUI::Initialize()
{
	/////////////////ファイル読み込んでステージの各オブジェクト設置///////////////////

	pCreateStage_->LoadFileCreateStage(this, "Stage/UserSelect/StageInformation/UserGameStartUI.txt");

	/////////////////画像・テクスチャのロード///////////////////

	//画像
	hCoinPict_ = Image::Load("Image/Coin/Coin.png");
	assert(hCoinPict_ >= ZERO);
	hStagePict_ = Image::Load("Image/UserSelect/Stage.png");
	assert(hStagePict_ >= ZERO);
	hCrossPict_ = Image::Load("Image/Coin/Cross.png");
	assert(hCrossPict_ >= ZERO);

	//テキストの初期化
	ARGUMENT_INITIALIZE(pText_, new Text);
	pText_->Initialize("Text/NumberFont.png", 128, 256, 10);
}


//更新
void UserGameStartUI::Update()
{
}

//描画
void UserGameStartUI::Draw()
{
	//コイン
	Transform t;
	ARGUMENT_INITIALIZE(t.scale_.x, 0.6f);
	ARGUMENT_INITIALIZE(t.scale_.y, 0.6f);
	ARGUMENT_INITIALIZE(t.position_.x, 0.30f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.40f);
	Image::SetTransform(hCoinPict_, t);
	Image::Draw(hCoinPict_);

	//ステージ
	ARGUMENT_INITIALIZE(t.position_.x, 0.30f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.7f);
	Image::SetTransform(hStagePict_, t);
	Image::Draw(hStagePict_);

	//クロス
	ARGUMENT_INITIALIZE(t.position_.x, 0.45f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.40f);
	Image::SetTransform(hCrossPict_, t);
	Image::Draw(hCrossPict_);
	ARGUMENT_INITIALIZE(t.position_.x, 0.45f);
	ARGUMENT_INITIALIZE(t.position_.y, 0.7f);
	Image::SetTransform(hCrossPict_, t);
	Image::Draw(hCrossPict_);

	//テキスト
	pText_->NumberDraw(1500, 315, UserInfomation::GetCoinNum(), 0.8f, 0.02f);
	pText_->NumberDraw(1500, 155, UserInfomation::GetStageReleaseNum(), 0.8f, 0.01f);
}