#include "MiniGameLevelSelectScene.h"
#include "MiniGameLevelSelectStage.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Gimmick/Warp.h"

//�R���X�g���N�^
MiniGameLevelSelectScene::MiniGameLevelSelectScene(GameObject* parent)
	: GameObject(parent, "MiniGameLevelSelectScene"), hAudio_(-1)
{
}

//�f�X�g���N�^
MiniGameLevelSelectScene::~MiniGameLevelSelectScene()
{
	Audio::Stop(hAudio_);
}

//������
void MiniGameLevelSelectScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<MiniGameLevelSelectStage>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/MiniGame/MiniGameSelect.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void MiniGameLevelSelectScene::Update()
{
}

//�`��
void MiniGameLevelSelectScene::Draw()
{
}

//�J��
void MiniGameLevelSelectScene::Release()
{
}

void MiniGameLevelSelectScene::StartUpdate()
{
}
