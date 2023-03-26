#include "StageSelectScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Scene/StageSelectScene/StageSelectStage.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"

//�R���X�g���N�^
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"), hAudio_(-1)
{
}

//�f�X�g���N�^
StageSelectScene::~StageSelectScene()
{
	Audio::Stop(hAudio_);
}

//������
void StageSelectScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<StageSelectStage>(this));

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/Home/Home.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void StageSelectScene::Update()
{
}

//�`��
void StageSelectScene::Draw()
{
}
