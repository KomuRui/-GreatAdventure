#include "BossEnemyMovie.h"
#include "../Manager/CoinManager/CoinManager.h"
#include "../Player/PlayerMovie.h"
#include "../Engine/ResourceManager/Fade.h"
#include "../Engine/ResourceManager/Audio.h"
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
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie"), addScaleValue_(ZERO), hAudio_(-1), isChangeTalk_(false)
{}

//�f�X�g���N�^
BossEnemyMovie::~BossEnemyMovie()
{
	Audio::Stop(hAudio_);
}

//������
void BossEnemyMovie::ChildInitialize()
{
	//�R�C����1�z���������ɉ��Z����l��ݒ�
	ARGUMENT_INITIALIZE(addScaleValue_, 2.0f / CoinManager::GetCoinNum());

	//���邳�ݒ�
	Model::SetBrightness(hModel_, 1.0f);

	//�b���Ă��鎞�̉摜�E�e�L�X�g�\��
	ARGUMENT_INITIALIZE(pTalkImage_, Instantiate<TalkImage>(GetParent()->GetParent()->GetParent()));
	pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie.csv");

	//�����[�h
	hAudio_ = Audio::Load("Audio/BGM/World2/Movie1.wav");
	assert(hAudio_ >= ZERO);

	//��
	//Audio::PlayLoop(hAudio_);
}

//�X�V
void BossEnemyMovie::ChildUpdate()
{
	//Player�̕�������
	LookObject(((PlayerMovie*)FindObject("Player"))->GetPosition(), vNormal_);

	//�����Ō�܂ŕ`�悳��Ă��Ă���b���ύX����Ă���X�{�^�����������̂Ȃ�
	if (pTalkImage_->IsLastDraw() && isChangeTalk_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		//�摜�폜
		pTalkImage_->KillMe();

		//�t�F�[�h�C��
		Fade::SetFadeStatus(FADE_NORMAL_IN);
	}

	//�{�X�̃X�e�[�W���t�F�[�h���Ō�܂ŏI�����Ă�����X�e�[�W���폜���ă��[�r�[�̃V�[���쐬
	if (Fade::isNormalFadeNotTransparency())
	{
		//�폜
		GameManager::GetpStage()->GetCreateStage()->AllCreateStageDelete();

		//�{�X�X�e�[�W�쐬
		((WorldStage2*)GetParent())->CreateBossStage();

		//�t�F�[�h�A�E�g
		Fade::SetFadeStatus(FADE_NORMAL_OUT);
	}
}

//�g�傷��
void BossEnemyMovie::AddScale()
{
	//�g��
	ARGUMENT_INITIALIZE(transform_.scale_,Float3Add(transform_.scale_, { addScaleValue_,addScaleValue_,addScaleValue_ }));

	//�����R�C��������0�Ȃ�b�����e���`�F���W����
	if (CoinManager::GetCoinNum() <= ZERO && pTalkImage_->IsLastDraw() && !isChangeTalk_)
	{
		ARGUMENT_INITIALIZE(isChangeTalk_, true);
		pTalkImage_->GetText()->ResetTotalDrawNum();
		pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie2.csv");
	}
}