#include "Combo.h"
#include "../Engine/Global.h"

//�R���X�g���N�^
Combo::Combo()
	:pComboText_(new Text), pComboNumText_(new Text), comboPositiom_(ZERO,ZERO),numberPositiom_(ZERO,ZERO),
	ComboTotalCount_(ZERO), scale_(1)
{};

//������
void Combo::Initialize()
{
	//�e�L�X�g�̏�����
	pComboText_->Initialize();
	pComboNumText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//�e�L�X�g�̃|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(comboPositiom_.x,1450);
	ARGUMENT_INITIALIZE(comboPositiom_.y,400);

	//�����̃|�W�V�����ݒ�
	ARGUMENT_INITIALIZE(numberPositiom_.x,1590);
	ARGUMENT_INITIALIZE(numberPositiom_.y,260);
}

//�`��
void Combo::Draw()
{
	//�R���{����0����Ȃ����
	if (ComboTotalCount_ != ZERO)
	{
		//�R���{�`��
		pComboText_->Draw(comboPositiom_.x, comboPositiom_.y, L"COMBO", 0.5f);
		pComboNumText_->NumberDraw(numberPositiom_.x, numberPositiom_.y, ComboTotalCount_, scale_);
	}
}

//�R���{���Z
void Combo::AddCombo() { ComboTotalCount_++; }

//�����̊g�嗦�Z�b�g
void Combo::SetTextScale(const float& scale) { scale_ = scale; }

//�R���{�̐����Z�b�g
void Combo::ComboReset() { ComboTotalCount_ = ZERO; }
