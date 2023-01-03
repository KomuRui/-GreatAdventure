#include <stdlib.h>
#include "Direct3D.h"
#include "Text.h"
#include "Global.h"
#include "../Manager/TextManager/TextManager.h"

Text::Text() : hPict_(-1), width_(128), height_(256), fileName_("Text/MainFont.png"), rowLength_(10), speed_(1.0f), fpsCount_(0), totalDrawNum_(1)
{
}

Text::~Text()
{
}

//�������i�f�t�H���g�j
HRESULT Text::Initialize(float speed)
{

	//�摜�̃��[�h
	hPict_ = Image::Load(fileName_);
	assert(hPict_ >= 0);

	//60FPS�Ɖ��肷��
	speed_ = speed * 60; 

	return S_OK;
}

//�������i�I���W�i���̉摜�j
HRESULT Text::Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength, float speed)
{
	strcpy_s(fileName_, fileName);
	width_ = charWidth;
	height_ = charHeight;
	rowLength_ = rowLength;
	speed_ = speed * 60; //60FPS�Ɖ��肷��
	return Initialize();
}


//�`��i������:�����j
void Text::NumberDraw(int x, int y, const char* str, float ratio)
{
	//�\���ʒu�i����j���v�Z
	//Sprite�N���X�͒��S��(0,0)�A�E�オ(1,1)�Ƃ������W�����A�����̈����͍����(0,0)�A�h�b�g�P�ʂŎw�肵�Ă���
	float px, py;

	//�����͍��㌴�_�����A�X�v���C�g�͉�ʒ��������_�Ȃ̂ŁA��ʃT�C�Y�̔������炷
	px = (float)(x - Direct3D::screenWidth_ / 2);
	py = (float)(-y + Direct3D::screenHeight_ / 2);	//Y����+-���]

	//�X�v���C�g��Position��1���炷�Ɖ�ʃT�C�Y�̔��������̂ŁA�s�N�Z���P�ʂɕϊ�
	px /= (float)(Direct3D::screenWidth_ / 2.0f);
	py /= (float)(Direct3D::screenHeight_ / 2.0f);


	//�P�������\������
	for (int i = 0; str[i] != '\0'; i++)	//������̖����܂ŗ�����I���
	{
		//�\���������������A�摜�̉��Ԗڂɏ����Ă��邩�����߂�
		int id = str[i] - '0';

		//�\���������������A�摜�̂ǂ��ɂ��邩�����߂�
		int x = id % rowLength_;	//�����牽�Ԗ�
		int y = id / rowLength_;	//�ォ�牽�Ԗ�

		//�\������ʒu
		Transform transform;
		transform.position_.x = px;
		transform.position_.y = py;

		//�傫��
		transform.scale_.x *= ratio;
		transform.scale_.y *= ratio;

		Image::SetTransform(hPict_, transform);

		//�\������͈�
		Image::SetRect(hPict_, width_ * x , height_ * y, width_, height_);

		//�\��
		Image::Draw(hPict_);

		//���̈ʒu�ɂ��炷
		px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f) * transform.scale_.x) - 0.05;
	}
}

//�`��i������j�ꕶ�����Ƃɏ��X�ɕ\������
void Text::SlowlyDraw(int x, int y, const char* str, float ratio)
{
	//�\���ʒu�i����j���v�Z
	//Sprite�N���X�͒��S��(0,0)�A�E�オ(1,1)�Ƃ������W�����A�����̈����͍����(0,0)�A�h�b�g�P�ʂŎw�肵�Ă���
	float px, py;

	//�����͍��㌴�_�����A�X�v���C�g�͉�ʒ��������_�Ȃ̂ŁA��ʃT�C�Y�̔������炷
	px = (float)(x - Direct3D::screenWidth_ / 2);
	py = (float)(-y + Direct3D::screenHeight_ / 2);	//Y����+-���]

	//�X�v���C�g��Position��1���炷�Ɖ�ʃT�C�Y�̔��������̂ŁA�s�N�Z���P�ʂɕϊ�
	px /= (float)(Direct3D::screenWidth_ / 2.0f);
	py /= (float)(Direct3D::screenHeight_ / 2.0f);

	//�P�������\������
	for (int i = 0; str[i] != '\0'; i++)	//������̖����܂ŗ�����I���
	{
		//�����\�����Ă�������菬�����Ȃ�
		if (i < totalDrawNum_)
		{
			//�����R���}�Ȃ���s
			if (str[i] == ',')
			{
				//�\������X��������
				px = (float)(x - Direct3D::screenWidth_ / 2);
				px /= (float)(Direct3D::screenWidth_ / 2.0f);

				//Y���������炷
				py -= 0.2f;
			}
			else
			{
				int g = TextManager::GetNumber(str[i]);
				//�\���������������A�摜�̉��Ԗڂɏ����Ă��邩�����߂�
				int id = str[i] - '0';

				//�\���������������A�摜�̂ǂ��ɂ��邩�����߂�
				int x = id % rowLength_;	//�����牽�Ԗ�
				int y = id / rowLength_;	//�ォ�牽�Ԗ�

				//�\������ʒu
				Transform transform;
				transform.position_.x = px;
				transform.position_.y = py;

				//�傫��
				transform.scale_.x *= ratio;
				transform.scale_.y *= ratio;

				Image::SetTransform(hPict_, transform);

				//�\������͈�
				Image::SetRect(hPict_, width_ * x, height_ * y, width_, height_);

				//�\��
				Image::Draw(hPict_);

				//���̈ʒu�ɂ��炷
				px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f) * transform.scale_.x) - 0.05;
			}
		}
		else
			break;
	}

	//1�����₷
	fpsCount_++;

	//����fpsCount_���X�s�[�h���傫���Ȃ�����
	if (fpsCount_ > speed_)
	{
		ARGUMENT_INITIALIZE(fpsCount_, ZERO);
		totalDrawNum_++;
	}
}

//�`��i�����l�j
void Text::NumberDraw(int x, int y, int value, float ratio)
{
	//������ɕϊ�
	char str[256];
	sprintf_s(str, "%d", value);

	NumberDraw(x, y, str, ratio);
}

//�`��i�����l�j�ꕶ�����Ƃɏ��X�ɕ\������
void Text::SlowlyDraw(int x, int y, int value, float ratio)
{
	//������ɕϊ�
	char str[256];
	sprintf_s(str, "%d", value);

	SlowlyDraw(x, y, str, ratio);
}

//���
void Text::Release()
{
	Image::Release(hPict_);
}
