#include "UserSelectSceneUI.h"

//�萔
namespace
{
	static const wchar_t DRAW_TEXT[] = L"��-�U-�Z���N�g"; //�`�悷�镶��
	static const float DRAW_SPEED = 0.2f;                 //�`�摬�x
	static const int DRAW_X = 100;                        //�`��ʒuX
	static const int DRAW_Y = 100;                        //�`��ʒuY
}

//�R���X�g���N�^
UserSelectSceneUI::UserSelectSceneUI(GameObject* parent)
	: GameObject(parent, "UserSelectSceneUI"), sceneNameText(new Text)
{
}

//������
void UserSelectSceneUI::Initialize()
{
	//������
	sceneNameText->Initialize();
	sceneNameText->SetDrawSpeed(DRAW_SPEED);
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void UserSelectSceneUI::StartUpdate()
{
}

//�X�V
void UserSelectSceneUI::Update()
{
}

//�`��
void UserSelectSceneUI::Draw()
{
	//�Ō�܂ŕ`�悳�ꂽ��ŏ�����`�悵����
	if (sceneNameText->SlowlyDraw(DRAW_X, DRAW_Y, DRAW_TEXT))
		sceneNameText->SetTotalDrawNum(ZERO);
}

//���
void UserSelectSceneUI::Release()
{
}
