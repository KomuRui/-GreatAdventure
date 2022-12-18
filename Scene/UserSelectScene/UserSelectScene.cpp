#include "UserSelectScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "../../Engine/CreateStage.h"

//�R���X�g���N�^
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene"), hModel_(-1)
{
}

//������
void UserSelectScene::Initialize()
{
	///////////////�t�F�[�h�C��///////////////////

	GameManager::SetStatus(FADE_IN);

	///////////////�摜�f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Stage/UserSelect/Model/BackGroundModel.fbx");
	assert(hModel_ >= ZERO);

	//�w�i�̃��f�����������点��
	Model::SetBrightness(hModel_, BRIGHTNESS);

	/////////////////�X�e�[�W�ݒu���邽�߂ɕK�v��GUI///////////////////

	Instantiate<ImGuiSet>(GetParent());
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void UserSelectScene::StartUpdate()
{
}

//�X�V
void UserSelectScene::Update()
{
	//�w�i��]
	transform_.rotate_.y += RATATION_SPEED;
}

//�`��
void UserSelectScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void UserSelectScene::Release()
{
}

