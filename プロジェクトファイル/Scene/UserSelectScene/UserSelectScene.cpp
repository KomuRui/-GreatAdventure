#include "UserSelectScene.h"
#include "../../Engine/ResourceManager/Image.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Model.h"
#include "../../Engine/ResourceManager/CreateStage.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "UserSelectStage.h"

//�R���X�g���N�^
UserSelectScene::UserSelectScene(GameObject* parent)
	: GameObject(parent, "UserSelectScene"), hAudio_(-1)
{
}

//�f�X�g���N�^
UserSelectScene::~UserSelectScene()
{
	Audio::Stop(hAudio_);
}

//������
void UserSelectScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<UserSelectStage>(this));

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/Title/Title.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);
}

//�X�V�̑O�Ɉ�x�����Ă΂��X�V
void UserSelectScene::StartUpdate()
{
}

//�X�V
void UserSelectScene::Update()
{
}

//�`��
void UserSelectScene::Draw()
{
}

//�J��
void UserSelectScene::Release()
{
}

