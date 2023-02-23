#include "PrincessIconButton.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../../Engine/ResourceManager/Image.h"
#include "../IconSelectUI.h"

//�萔
namespace
{
	//���̃A�C�R���̃��f���p�X
	static const std::string ICON_MODEL_PATH = "Stage/UserSelect/Model/PrincessIconModel.fbx"; 

	//����
	static const wchar_t DRAW_TEXT[] = L"�s-�����";  //�`�悷�镶��
	static const int DRAW_X = 700;                    //�`��ʒuX
	static const int DRAW_Y = 850;                    //�`��ʒuY
}

//�R���X�g���N�^
PrincessIconButton::PrincessIconButton(GameObject* parent, std::string modelPath, std::string name)
	:ButtonBase(parent, modelPath, name), hNotSelectPict_(-1), hSelectPict_(-1), NameText(new Text)
{}

//������
void PrincessIconButton::ChildInitialize()
{
	//������
	NameText->Initialize();

	//�Z���N�g�摜�̔ԍ��擾
	ARGUMENT_INITIALIZE(hNotSelectPict_, hPict_);

	//���[�h
	ARGUMENT_INITIALIZE(hSelectPict_, Image::Load("Image/UserSelect/IconSelect/PrincessIcon_Select.png"));
}

//�{�^���������ꂽ�牽���邩
void PrincessIconButton::IsButtonPush()
{
	//�e�ɉ����ꂽ���Ƃ��
	((IconSelectUI*)GetParent())->ChangeEasingMove(ICON_MODEL_PATH);
}

//�`��
void PrincessIconButton::ChildDraw()
{
	//�Ō�܂ŕ`�悳�ꂽ��ŏ�����`�悵����
	if(isSelect_)NameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void PrincessIconButton::IsButtonSelect() { ARGUMENT_INITIALIZE(hPict_, hSelectPict_); }

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void PrincessIconButton::IsButtonSelectRelease() { ARGUMENT_INITIALIZE(hPict_, hNotSelectPict_); }
