#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Camera.h"
#include "TutorialStage.h"
#include "../Player.h"
#include "../Stage.h"
//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{

}

//������
void TutorialScene::Initialize()
{
	Instantiate<TutorialStage>(this);
	Instantiate<Player>(this);

	///////////////�摜�f�[�^�̃��[�h///////////////////

	hPict_[one] = Image::Load("Image/Tutorial/haikei.png");

	///////////////transform///////////////////

	t[one].position_.x = 0.5;

	///////////////�J����///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));

}

//�X�V
void TutorialScene::Update()
{
	if (Input::GetPadStickL().x > 0)
		t[one].position_.x -= Input::GetPadStickL().x / 1000;
	else if (Input::GetPadStickL().x < 0)
		t[one].position_.x -= Input::GetPadStickL().x / 1000;
}

//�`��
void TutorialScene::Draw()
{
	/*Image::SetTransform(hPict_[one], t[one]);
	Image::Draw(hPict_[one]);*/
}

//�J��
void TutorialScene::Release()
{
}

void TutorialScene::StartUpdate()
{
}
