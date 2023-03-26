#include "TutorialScene2.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Player/Player3D.h"
#include "../../Scene/TutorialScene/TutorialStage2.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Gimmick/Warp.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Engine/ResourceManager/Audio.h"

//�R���X�g���N�^
TutorialScene2::TutorialScene2(GameObject* parent)
	: GameObject(parent, "TutorialScene2"), hAudio_(-1)
{

}

//�f�X�g���N�^
TutorialScene2::~TutorialScene2()
{
	Audio::Stop(hAudio_);
}


//������
void TutorialScene2::Initialize()
{
	//���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g
	GameManager::SetpStage(Instantiate<TutorialStage2>(this));

	//Player�ƃ��[�v�̕\��
	GameManager::SetpPlayer(Instantiate<Player3D>(this));
	Warp* pWarp = Instantiate<Warp>(this, "Stage/Gimmick/Warp.fbx", "Warp");

	//���[�v�̃|�W�V�����ƈړ���̐ݒ�
	pWarp->SetPosition(GameManager::GetpStage()->GetPos());
	pWarp->SetWarpTarget(GameManager::GetpStage()->GetWarpTargetPos());
	pWarp->SetWarpType(MoveToPurpose);
	GameManager::SetpWarp(pWarp);

	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/Tutorial/TutorialScene.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);
}

//�X�V
void TutorialScene2::Update()
{
}

//�`��
void TutorialScene2::Draw()
{
}

//�J��
void TutorialScene2::Release()
{
}

void TutorialScene2::StartUpdate()
{
}
