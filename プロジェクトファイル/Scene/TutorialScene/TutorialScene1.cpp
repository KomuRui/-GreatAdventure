#include "TutorialScene1.h"
#include "../../Engine/SceneManager.h"
#include "../../Player/Player2D.h"
#include "../../Scene/TutorialScene/TutorialStage1.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Input.h"
#include "../../Engine/Audio.h"

//�R���X�g���N�^
TutorialScene1::TutorialScene1(GameObject* parent)
	: GameObject(parent, "TutorialScene1"),hAudio_(-1)
{

}

//������
void TutorialScene1::Initialize()
{
	//�X�e�[�W�̕\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpStage(Instantiate<TutorialStage1>(this));

	//Player�\��(���ꂩ��g���X�e�[�W�̃|�C���^��GameManager�ɃZ�b�g)
	GameManager::SetpPlayer(Instantiate<Player2D>(this));

	//�t�F�[�h�C��
	GameManager::SetStatus(FADE_IN);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/TutorialScene.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);
}

//�X�V�̑O�Ɉ�x�����Ă΂��֐�
void TutorialScene1::StartUpdate()
{
}

//�X�V
void TutorialScene1::Update()
{
	
	//�e�X�g�p
	if (Input::IsKeyDown(DIK_R))
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager"); 
		pScene->ChangeScene(SCENE_ID_TUTORIAL2);
	}
}

//�`��
void TutorialScene1::Draw()
{
}

//�J��
void TutorialScene1::Release()
{
}

