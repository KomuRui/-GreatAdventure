#include "MiniGameTime.h"
#include "../Engine/Global.h"
#include "../Engine/Time.h"
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
	:pTimeText_(new Text), pStartCountText_(new Text), startCount_(ZERO), startCountTextScale_(ZERO)
{
}

//������
void MiniGameTime::Initialize()
{
	//�����̏�����
	pTimeText_->Initialize(TEXT_INTERVAL);
	pStartCountText_->Initialize("Text/NumberFont.png", 128, 256, 10);

	//�X�^�[�g�J�E���g�̏�����
	ARGUMENT_INITIALIZE(startCount_, START_MAX_COUNT);
	ARGUMENT_INITIALIZE(startCountTextScale_, NORMAL_START_COUNT_SCALE);

}

//�`��
void MiniGameTime::Draw()
{
}

//�������ԕ`��
void MiniGameTime::LimitTimeDraw()
{
	//���C�h������i�[�p
	wchar_t wtext[FILENAME_MAX];
	std::string text;

	if (Time::GetTimef() < 30.0f)
	{
		//10�b�ȏ�Ȃ�
		if (Time::GetTimef() / 10.0f >= 0)
			text = float_to_string(Time::GetTimef(), 3) + "/30.000";
		else
			text = "0" + float_to_string(Time::GetTimef(), 3) + "/30.000";
	}
	else
	{
		//�\������^�C�����Œ�
	    ARGUMENT_INITIALIZE(text,"30.000/30.000");

		//�~�j�Q�[���I������
		MiniGameManager::ChangeMiniGameStatus(MiniGameStatus::END);

		//�t�F�[�h�̃X�e�[�^�X��FADE_OUT��Ԃ���Ȃ�������
		if (GameManager::GetStatus() != FADE_OUT)
			GameManager::SetStatus(FADE_OUT, "Image/Fade/BaseFade.png");

		//�^�C�������b�N����
		Time::Lock();
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
}
