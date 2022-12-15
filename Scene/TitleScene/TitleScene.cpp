#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hModel_(-1)
{
}

//������
void TitleScene::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("TitleScene/Model/BackGroundModel.fbx");
	//Model::SetBrightness(hModel_, 1.0f);

	///////////////�J����///////////////////

	Camera::SetPosition(XMFLOAT3(0, 0, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 1));

}

//�X�V
void TitleScene::Update()
{
}

//�`��
void TitleScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TitleScene::Release()
{
}

void TitleScene::StartUpdate()
{
}
