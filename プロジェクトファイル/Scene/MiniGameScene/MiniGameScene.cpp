#include "MiniGameScene.h"
#include "MiniGameStage.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/PlayerMiniGame.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../MiniGame/MiniGameSetObject.h"
#include "../../Engine/ResourceManager/Audio.h"

//�R���X�g���N�^
MiniGameScene::MiniGameScene(GameObject* parent)
	: GameObject(parent, "MiniGameScene"), hAudio_(-1)
{
}

//�f�X�g���N�^
MiniGameScene::~MiniGameScene()
{
	Audio::Stop(hAudio_);
}

//������
void MiniGameScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<MiniGameStage>(this));

	//Player�\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpPlayer(Instantiate<PlayerMiniGame>(this));

	//�I�u�W�F�N�g�Z�b�g�p
	Instantiate<MiniGameSetObject>(this);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/MiniGame/MiniGame.wav");
	assert(hAudio_ >= ZERO);

	//��
	//Audio::PlayLoop(hAudio_);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void MiniGameScene::Update()
{
}

//�`��
void MiniGameScene::Draw()
{
}

//�J��
void MiniGameScene::Release()
{
}

void MiniGameScene::StartUpdate()
{
}
