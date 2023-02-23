#include "DropIconButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../IconSelectUI.h"

//�萔
namespace
{
	//���̃A�C�R���̃��f���p�X
	static const std::string ICON_MODEL_PATH = "Stage/UserSelect/Model/DropIconModel.fbx";

	//����
	static const wchar_t DRAW_TEXT[] = L"�V�g����";  //�`�悷�镶��
	static const int DRAW_X = 750;                   //�`��ʒuX
	static const int DRAW_Y = 850;                   //�`��ʒuY
}

//�R���X�g���N�^
DropIconButton::DropIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1), NameText(new Text)
{}

//������
void DropIconButton::ChildInitialize()
{
	//������
	NameText->Initialize();

	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/DropIcon_Select.png"));
}

//�`��
void DropIconButton::ChildDraw()
{
	//�Ō�܂ŕ`�悳�ꂽ��ŏ�����`�悵����
	if (isSelect_)NameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//�{�^���������ꂽ�牽���邩
void DropIconButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((IconSelectUI*)GetParent())->ChangeEasingMove(ICON_MODEL_PATH);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void DropIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void DropIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }