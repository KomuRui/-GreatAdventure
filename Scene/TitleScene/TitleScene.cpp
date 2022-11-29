#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{

}

//������
void TitleScene::Initialize()
{
	Instantiate<Player>(this);

	///////////////�摜�f�[�^�̃��[�h///////////////////


	///////////////transform///////////////////


	///////////////�J����///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));

}

//�X�V
void TitleScene::Update()
{

	//A�{�^������������Play�V�[���ֈڍs
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
	}

	//Pad���Ȃ��Ƃ��Ɉڍs����p
	if (Input::IsKeyDown(DIK_RETURN))
	{
	}

}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}

void TitleScene::StartUpdate()
{
}
