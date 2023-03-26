#include "WorldScene1.h"
#include "../../../Manager/SceneManager/SceneManager.h"
#include "../../../Player/Player3D.h"
#include "../../../Manager/GameManager/GameManager.h"
#include "../../../Engine/DirectX/Input.h"
#include "../../../Engine/GameObject/Camera.h"
#include "../../../Engine/ResourceManager/Fade.h"
#include "../../../Engine/ResourceManager/Audio.h"
#include "../../../Gimmick/Warp.h"
#include "WorldStage1.h"

//�R���X�g���N�^
WorldScene1::WorldScene1(GameObject* parent)
	: GameObject(parent, "WorldScene1"), hAudio_(-1)
{
}

//�f�X�g���N�^
WorldScene1::~WorldScene1()
{
	Audio::Stop(hAudio_);
}

//������
void WorldScene1::Initialize()
{
	//�X�e�[�W�̕\��
	GameManager::SetpStage(Instantiate<WorldStage1>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/World1/World1.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
}

//�X�V
void WorldScene1::Update()
{
}

//�`��
void WorldScene1::Draw()
{
}

//�J��
void WorldScene1::Release()
{
}

void WorldScene1::StartUpdate()
{
}
