#include "StageSelectTextUI.h"

//�萔
namespace
{
	static const wchar_t DRAW_TEXT[] = L"�X�e-�W�Z���N�g";   //�`�悷�镶��
	static const int DRAW_X = 100;                           //�`��ʒuX
	static const int DRAW_Y = 100;                           //�`��ʒuY
}

//�R���X�g���N�^
StageSelectTextUI::StageSelectTextUI(GameObject* parent)
	: GameObject(parent, "StageSelectTextUI"), sceneNameText(new Text)
{
}

//������
void StageSelectTextUI::Initialize()
{
	//������
	sceneNameText->Initialize();
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void StageSelectTextUI::StartUpdate()
{
}

//�X�V
void StageSelectTextUI::Update()
{
}

//�`��
void StageSelectTextUI::Draw()
{
	//�Ō�܂ŕ`�悳�ꂽ��ŏ�����`�悵����
	sceneNameText->Draw(DRAW_X, DRAW_Y, DRAW_TEXT, 0.8f);
}

//���
void StageSelectTextUI::Release()
{
}
