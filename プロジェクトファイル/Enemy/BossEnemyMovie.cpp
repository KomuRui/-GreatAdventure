#include "BossEnemyMovie.h"
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
BossEnemyMovie::BossEnemyMovie(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,"Enemy/Model/MainBoss.fbx","BossEnemyMovie"), addScaleValue_(ZERO)
{}

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
}

//�X�V
void BossEnemyMovie::ChildUpdate()
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

	//�����ő�T�C�Y�ɂȂ�����b�����e���`�F���W����
	if (transform_.scale_.x >= MAX_SIZE && pTalkImage_->IsLastDraw())
	{
		pTalkImage_->GetText()->ResetTotalDrawNum();
		pTalkImage_->NewCsvFile("Stage/World/World2/MobTalk_Movie2.csv");
	}
}