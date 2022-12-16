#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/Light.h"
#include "../../Engine/CreateStage.h"

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
	assert(hModel_ >= ZERO);

	//�w�i�̃��f�����������点��
	Model::SetBrightness(hModel_, 1.5f);

	/////////////////�X�e�[�W�ݒu���邽�߂ɕK�v��GUI///////////////////

	Instantiate<ImGuiSet>(GetParent());

	/////////////////�t�@�C���ǂݍ���ŃX�e�[�W�̊e�I�u�W�F�N�g�ݒu///////////////////

	CreateStage* pCreateStage = new CreateStage;
	pCreateStage->LoadFile(GetParent(), "TitleScene/StageInformation/TitleScene1.txt");

	///////////////�J����///////////////////

	Camera::SetPosition(XMFLOAT3(0, 0, 5));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void TitleScene::StartUpdate()
{
}

//�X�V
void TitleScene::Update()
{
	transform_.rotate_.y += 0.5;
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

