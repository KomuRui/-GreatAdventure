#include "TalkImage.h"
#include "../Engine/ResourceManager/Image.h"
#include "../Engine/ResourceManager/Audio.h"
#include "../Engine/DirectX/Input.h"
#include "../Engine/GUI/ImGuiSet.h"
#include "../Engine/ResourceManager/CsvReader.h"
#include "../Manager/TextManager/TextManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/AudioManager/OtherAudioManager/OtherAudioManager.h"

//�萔
namespace
{
	//����
	static const float TEXT_SCALE = 0.3f;

	//�`��X�s�[�h
	static const float NORMAL_DRAW_SPEED = 0.1f; //����
	static const float FAST_DRAW_SPEED = 0.05f;  //����
}

//�R���X�g���N�^
TalkImage::TalkImage(GameObject* parent)
	: GameObject(parent, "TalkImage"), hBasePict_(-1),hCharaPict_(-1), hNextPict_(-1), drawTextNum_((int)ZERO),
	isLastDraw_(false), pText_(new Text), isButtonPushTextNext_(true), hAudio_(-1)
{
}

//�f�X�g���N�^
TalkImage::~TalkImage()
{
	//���~�߂�
	Audio::Stop(hAudio_);
}

//������
void TalkImage::Initialize()
{
	///////////////�����̃��[�h///////////////////

	//������
	pText_->Initialize(NORMAL_DRAW_SPEED);

	//�������O������擾
	pCsv_ = new CsvReader(TextManager::GetText(GameManager::GetpSceneManager()->GetSceneId()));

	///////////////�摜�E���f�[�^�̃��[�h///////////////////

	hBasePict_ = Image::Load("Image/Text/Talk.png");
	assert(hBasePict_ >= ZERO);

	//�{�X�̃V�[���Ȃ�
	if (GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_WORLD2)
	{
		hCharaPict_ = Image::Load("Image/MainMob/MainBossImage.png");
		assert(hCharaPict_ >= ZERO);
	}
	//���X�g�V�[���Ȃ�
	else if (GameManager::GetpSceneManager()->GetSceneId() == SCENE_ID_LAST)
	{
		hCharaPict_ = Image::Load("Image/Princess/PrincessImage.png");
		assert(hCharaPict_ >= ZERO);
	}
	//����ȊO�Ȃ�
	else
	{
		hCharaPict_ = Image::Load("Image/MainMob/MainMobImage.png");
		assert(hCharaPict_ >= ZERO);
	}

	hNextPict_ = Image::Load("Image/Text/Next.png");
	assert(hNextPict_ >= ZERO);

	hAudio_ = Audio::Load("Audio/SE/Mob/Talk.wav");
	assert(hAudio_ >= ZERO);

	Audio::PlayLoop(hAudio_);

	/////////////////////////�eTransform/////////////////////////

	//�x�[�X
	ARGUMENT_INITIALIZE(tBase_.position_.x, GetPrivateProfilefloat("POSITION", "BaseX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.y, GetPrivateProfilefloat("POSITION", "BaseY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.position_.z,1.0f);

	ARGUMENT_INITIALIZE(tBase_.scale_.x, GetPrivateProfilefloat("SCALE", "BaseX", "2.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.y, GetPrivateProfilefloat("SCALE", "BaseY", "0.8", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tBase_.scale_.z, 1.0f);

	//�L����
	ARGUMENT_INITIALIZE(tChara_.position_.x, GetPrivateProfilefloat("POSITION", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.y, GetPrivateProfilefloat("POSITION", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tChara_.scale_.x, GetPrivateProfilefloat("SCALE", "CharaX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.y, GetPrivateProfilefloat("SCALE", "CharaY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tChara_.scale_.z, 1.0f);

	//Next
	ARGUMENT_INITIALIZE(tNext_.position_.x, GetPrivateProfilefloat("POSITION", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.y, GetPrivateProfilefloat("POSITION", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.position_.z, 1.0f);

	ARGUMENT_INITIALIZE(tNext_.scale_.x, GetPrivateProfilefloat("SCALE", "NextX", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.y, GetPrivateProfilefloat("SCALE", "NextY", "1", "Image/Text/TextImagePosition.ini"));
	ARGUMENT_INITIALIZE(tNext_.scale_.z, 1.0f);
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void TalkImage::StartUpdate()
{
}

//�X�V
void TalkImage::Update()
{
	//B��������Ă���̂Ȃ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_X))
		pText_->SetDrawSpeed(FAST_DRAW_SPEED);
	else
		pText_->SetDrawSpeed(NORMAL_DRAW_SPEED);
}

//�`��
void TalkImage::Draw()
{
	/////////////////////////////�摜�`��///////////////////////////

	Image::SetTransform(hBasePict_, tBase_);
	Image::Draw(hBasePict_);

	Image::SetTransform(hCharaPict_, tChara_);
	Image::SetUi(hCharaPict_); //��O�ɕ\�����邽��SetUi���g��

	/////////////////////////////���������C�h������ɕϊ�///////////////////////////

    wchar_t wtext[FILENAME_MAX];
	std::string text = pCsv_->GetString(drawTextNum_, (int)ZERO);
	size_t ret;
	setlocale(LC_ALL, ".932");
	mbstowcs_s(&ret, wtext, text.c_str(), strlen(text.c_str()));

	///////////////////�����`��:�����������Ō�܂ŕ`�悵�Ă�����///////////////////

	if (pText_->SlowlyDraw(1050, 800, wtext, TEXT_SCALE))
	{
		//�Ō�̕������`�悵�I����Ă���̂Ȃ�
		if (drawTextNum_ >= pCsv_->GetLines() - 1)
			ARGUMENT_INITIALIZE(isLastDraw_, true);

		//�����{�^���������ĕ���������֍X�V����̂Ȃ��
		if (isButtonPushTextNext_)
		{
			//Next�摜��\��
			Image::SetTransform(hNextPict_, tNext_);
			Image::SetUi(hNextPict_);

			//���~�߂�
			Audio::Stop(hAudio_);

			//����������֍X�V
			ButtonPushDrawTextNext();
		}
		else
			Audio::Stop(hAudio_);

	}
}

//���
void TalkImage::Release()
{
}


//�{�^���������ĕ`�悷�镶��������̕�����ɍX�V����
void TalkImage::ButtonPushDrawTextNext()
{
	//����X�{�^�����������Ȃ玟�̕������
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X))
	{
		OtherAudioManager::ClickAudio(); //�N���b�N��
		Audio::PlayLoop(hAudio_);        //��b�����[�v
		NextText();
	}
}

//���̕������
void TalkImage::NextText()
{
	//�`�悷�镶����ύX
	drawTextNum_++;

	//�`��ł��镶��������������
	pText_->SetTotalDrawNum((int)ZERO);

	//�ő啶����ȏォ���[�v����Ȃ珉����
	if (drawTextNum_ >= pCsv_->GetLines())
		ARGUMENT_INITIALIZE(drawTextNum_, (int)ZERO);
}


//�V����Csv�ǂݍ��݂�����
void TalkImage::NewCsvFile(std::string fileNamePath)
{
	//�ǂݍ���
	ARGUMENT_INITIALIZE(pCsv_,new CsvReader(fileNamePath));

	//������
	ARGUMENT_INITIALIZE(isLastDraw_, false);
}
