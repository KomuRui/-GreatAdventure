#include "PigIconButton.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Image.h"
#include "../NewFileUI.h"

//�萔
namespace
{
	static const wchar_t DRAW_TEXT[] = L"�s�N����";   //�`�悷�镶��
	static const int DRAW_X = 750;                    //�`��ʒuX
	static const int DRAW_Y = 850;                    //�`��ʒuY
}

//�R���X�g���N�^
PigIconButton::PigIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1), NameText(new Text)
{}

//������
void PigIconButton::ChildInitialize()
{
	//������
	NameText->Initialize();

	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/PigIcon_Select.png"));
}

//�`��
void PigIconButton::ChildDraw()
{
	//�Ō�܂ŕ`�悳�ꂽ��ŏ�����`�悵����
	if (isSelect_)NameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//�{�^���������ꂽ�牽���邩
void PigIconButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((NewFileUI*)GetParent())->ChangeEasingMove();
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void PigIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void PigIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }