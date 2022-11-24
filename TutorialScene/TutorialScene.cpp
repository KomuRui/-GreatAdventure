#include "TutorialScene.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Camera.h"
#include "TutorialStage.h"
#include "../Player.h"
#include "../Gimmick/Signboard.h"

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{

}

//������
void TutorialScene::Initialize()
{
	Instantiate<TutorialStage>(this);
	Instantiate<Signboard>(this,"Image/Tutorial/MoveOperate.png");
	Instantiate<Player>(this);
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
