#include "Princess.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"
#include "../Engine/ResourceManager/Fade.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Engine/ResourceManager/CreateStage.h"
#include "../Scene/WorldScene/World2/WorldStage2.h"

//�萔
namespace
{
	//�ő�T�C�Y
	static const float MAX_SIZE = 3.0f;
}


//�R���X�g���N�^
Princess::Princess(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, "Enemy/Model/MainBoss.fbx", "Princess")
{}

//������
void Princess::ChildInitialize()
{
	//�b���Ă��鎞�̉摜�E�e�L�X�g�\��
	ARGUMENT_INITIALIZE(pTalkImage_, Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));
}

//�X�V
void Princess::ChildUpdate()
{
	//Player�̕�������
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);

	//�����Ō�܂ŕ`�悳��Ă��Ă��ő�T�C�Y��X�{�^�����������̂Ȃ�
	if (pTalkImage_->IsLastDraw() && transform_.scale_.x >= MAX_SIZE && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�摜�폜
		pTalkImage_->KillMe();

		//�t�F�[�h�C��
		Fade::SetFadeStatus(FADE_NORMAL_IN);
	}

	//�{�X�̃X�e�[�W���t�F�[�h���Ō�܂ŏI�����Ă�����X�e�[�W���폜���ă��[�r�[�̃V�[���쐬
	if (Fade::isNormalFadeNotTransparency())
	{
		//�t�F�[�h�A�E�g
		Fade::SetFadeStatus(FADE_NORMAL_OUT);
	}
}

