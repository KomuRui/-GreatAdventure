#include "MiniGameTime.h"
#include "../Engine/Global.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const int START_MAX_COUNT = 4;      			//�X�^�[�g�J�E���g�̍ő�l
	static const float TEXT_INTERVAL = -0.06f;		    //�����̊Ԋu
	static const float NORMAL_START_COUNT_SCALE = 5.0f; //�X�^�[�g�J�E���g�����̊g�嗦
}

//�R���X�g���N�^
MiniGameTime::MiniGameTime()
	:pTimeText_(new Text), pStartCountText_(new Text), startCount_(ZERO), startCountTextScale_(ZERO), timerhNum_(ZERO)
{
}

//������
void MiniGameTime::Initialize()
{
	//�^�C�}�[�쐬
	ARGUMENT_INITIALIZE(timerhNum_, Time::Add());

	//�����̏�����
	pTimeText_->Initialize(TEXT_INTERVAL);
	pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//�X�^�[�g�J�E���g�̏�����
	ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT);
	ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

}

//�������ԕ`��
void MiniGameTime::LimitTimeDraw()
{
	//���C�h������i�[�p
	wchar_t wtext[FILENAME_MAX];
	std::string text;

	if (Time::GetTimef(timerhNum_) < 30.0f)
	{
		//10�b�ȏ�Ȃ�
		if (Time::GetTimef(timerhNum_) / 10.0f >= ZERO)
			text = float_to_string(Time::GetTimef(timerhNum_), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(timerhNum_), 3) + "/30.000";
	}
	else
	{
		//�\������^�C�����Œ�
	    ARGUMENT_INITIALIZE(text,"30.000/30.000");

		//�~�j�Q�[���I������
		MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::END);

		//�t�F�[�h�̃X�e�[�^�X��FADE_OUT��Ԃ���Ȃ�������
		if (GameManager::GetFadeStatus() != FADE_CIRCLE_OUT)
			GameManager::SetFadeStatus(FADE_CIRCLE_OUT, "Image/Fade/BaseFade.png");

		//�^�C�������b�N����
		Time::Lock(timerhNum_);
	}

	//���C�h������ɕϊ�
	size_t ret;
	setlocale(LC_ALL, ".932");
	mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

	//���ԕ`��
	pTimeText_->Draw(100, 150, wtext, 1.0f, TEXT_INTERVAL);
}

//�X�^�[�g�J�E���g�`��
void MiniGameTime::StartCountDraw()
{
	//�������b�N����Ă���̂Ȃ烍�b�N����
	if (Time::isLock(timerhNum_)) Time::UnLock(timerhNum_);

	//��O�ۑ�
	int beforStartCount = startCount_;

	//startCount_�����߂�
	ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT - Time::GetTimei(timerhNum_));

	//�O��ƈႤ�̂Ȃ�g�嗦���ɖ߂�
	if (beforStartCount != startCount_) ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);


	//startCount_��0�Ȃ�
	if (startCount_ == ZERO)
	{
		//Start�`��
		pTimeText_->Draw(460, 440, L"START", 3.0f, -0.15f);
	}
	//�}�C�i�X�Ȃ�J�n
	else if (startCount_ < ZERO)
	{
		//�~�j�Q�[���J�n����
		MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::PLAY);

		//�^�C�����Z�b�g
		Time::Reset(timerhNum_);
	}
	//startCount_��3�ȉ��Ȃ琔���`��
	else if (startCount_ <= 3)
	{
		//�g�嗦�����������Ă���
		startCountTextScale_ -= 0.05f;

		//�`��
		pStartCountText_->NumberDraw(960, 440, startCount_, startCountTextScale_);
	}
}
