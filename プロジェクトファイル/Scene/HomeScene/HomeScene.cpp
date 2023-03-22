#include "HomeScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../Player/Player3D.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Scene/HomeScene/HomeStage.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Gimmick/Warp.h"

//�R���X�g���N�^
HomeScene::HomeScene(GameObject* parent)
	: GameObject(parent, "HomeScene"), hAudio_(-1)
{
}

//�f�X�g���N�^
HomeScene::~HomeScene()
{
	Audio::Stop(hAudio_);
}

//������
void HomeScene::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<HomeStage>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/Home/Home.wav");
	assert(hAudio_ >= ZERO);

	//��
	//Audio::PlayLoop(hAudio_);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void HomeScene::Update()
{
}

//�`��
void HomeScene::Draw()
{
}

//�J��
void HomeScene::Release()
{
}

void HomeScene::StartUpdate()
{
}
