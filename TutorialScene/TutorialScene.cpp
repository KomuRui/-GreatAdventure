#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Camera.h"
#include "TutorialStage.h"
#include "../Player.h"
#include "../Stage.h"
#include "../Engine/ImGuiSet.h"

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
	ImGuiSet *a = Instantiate<ImGuiSet>(this);

	a->CreateStage("TutorialStage1.txt");

	///////////////�摜�f�[�^�̃��[�h///////////////////


	///////////////transform///////////////////


	///////////////�J����///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));

}

//�X�V
void TutorialScene::Update()
{
}

//�`��
void TutorialScene::Draw()
{
}

//�J��
void TutorialScene::Release()
{
}

void TutorialScene::StartUpdate()
{
}
