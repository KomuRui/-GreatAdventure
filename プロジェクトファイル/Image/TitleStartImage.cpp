#include "TitleStartImage.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
TitleStartImage::TitleStartImage(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), ModelNamePath_(modelPath)
{
	for (int i = ZERO; i < MAX_IMAGE_TYPE; i++)
	{
		//������
		ARGUMENT_INITIALIZE(hPict_[i], -1);
	}
}

//������
void TitleStartImage::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////

	//�f�t�H���g
	hPict_[Default] = Image::Load(ModelNamePath_);
	assert(hPict_ >= ZERO);

	//A��������Ă�Ƃ�
	hPict_[A_Select] = Image::Load("Image/Title/Start_A_Select.png");
	assert(hPict_ >= ZERO);

	//RT��������Ă�Ƃ�
	hPict_[RT_Select] = Image::Load("Image/Title/Start_RT_Select.png");
	assert(hPict_ >= ZERO);

	//���ׂĂ�������Ă�Ƃ�
	hPict_[All_Select] = Image::Load("Image/Title/Start_ALL_Select.png");
	assert(hPict_ >= ZERO);
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void TitleStartImage::StartUpdate()
{
}

//�X�V
void TitleStartImage::Update()
{
	//����A��RT��������Ă�Ȃ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) || Input::GetPadTrrigerR())
	{
		ARGUMENT_INITIALIZE(transform_.scale_, AFTER_SCALE);
	}
	else
		ARGUMENT_INITIALIZE(transform_.scale_, BEFORE_SCALE);
}

//�`��
void TitleStartImage::Draw()
{
	//����A��RT��������������Ă�Ȃ�
	if (Input::IsPadButton(XINPUT_GAMEPAD_A) && Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_[All_Select], transform_);
		Image::Draw(hPict_[All_Select]);
	}
	//����A��������Ă���Ȃ�
	else if (Input::IsPadButton(XINPUT_GAMEPAD_A))
	{
		Image::SetTransform(hPict_[A_Select], transform_);
		Image::Draw(hPict_[A_Select]);
	}
	//����RT��������Ă���Ȃ�
	else if (Input::GetPadTrrigerR())
	{
		Image::SetTransform(hPict_[RT_Select], transform_);
		Image::Draw(hPict_[RT_Select]);
	}
	//��������������Ă��Ȃ��Ȃ�
	else
	{
		Image::SetTransform(hPict_[Default], transform_);
		Image::Draw(hPict_[Default]);
	}
	
}

//���
void TitleStartImage::Release()
{
}
