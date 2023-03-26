#include "EndRolesScene.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../Engine/ResourceManager/Fade.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/GameObject/Camera.h"
#include "../../UI/EndRolesScene/EndRoles.h"
#include "../../Engine/ResourceManager/Audio.h"


//�R���X�g���N�^
EndRolesScene::EndRolesScene(GameObject* parent)
	: GameObject(parent, "EndRolesScene"),hAudio_(-1)
{
}

//�f�X�g���N�^
EndRolesScene::~EndRolesScene()
{
	//���~�߂�
	Audio::Stop(hAudio_);
}

//������
void EndRolesScene::Initialize()
{
	//�G���h���[���\��
	Instantiate<EndRoles>(this,"Image/EndRole/EndRoleImage.png","EndRoles");

	//�t�F�[�h�A�E�g
	Fade::SetFadeStatus(FADE_NORMAL_OUT);

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/EndRole/EndRole.wav");
	assert(hAudio_ >= ZERO);

	//��
	Audio::PlayLoop(hAudio_);
}

//�X�V
void EndRolesScene::Update()
{
}

//�`��
void EndRolesScene::Draw()
{
}

//�J��
void EndRolesScene::Release()
{
}

void EndRolesScene::StartUpdate()
{
}