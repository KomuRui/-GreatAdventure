#include "Combo.h"
#include "../Engine/Global.h"

//コンストラクタ
Combo::Combo()
	:pComboText_(new Text), pComboNumText_(new Text), comboPositiom_(ZERO,ZERO),numberPositiom_(ZERO,ZERO),
	ComboTotalCount_(ZERO), scale_(1)
{};

//初期化
void Combo::Initialize()
{
	//テキストの初期化
	pComboText_->Initialize();
	pComboNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//テキストのポジション設定
	ARGUMENT_INITIALIZE(comboPositiom_.x,1450);
	ARGUMENT_INITIALIZE(comboPositiom_.y,400);

	//数字のポジション設定
	ARGUMENT_INITIALIZE(numberPositiom_.x,1590);
	ARGUMENT_INITIALIZE(numberPositiom_.y,260);
}

//描画
void Combo::Draw()
{
	//コンボ数が0じゃなければ
	if (ComboTotalCount_ != ZERO)
	{
		//コンボ描画
		pComboText_->Draw(comboPositiom_.x, comboPositiom_.y, L"COMBO", 0.5f);
		pComboNumText_->NumberDraw(numberPositiom_.x, numberPositiom_.y, ComboTotalCount_, scale_);
	}
}

//コンボ加算
void Combo::AddCombo() { ComboTotalCount_++; }

//文字の拡大率セット
void Combo::SetTextScale(const float& scale) { scale_ = scale; }

//コンボの数リセット
void Combo::ComboReset() { ComboTotalCount_ = ZERO; }
