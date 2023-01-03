#pragma once
#include "Image.h"

/// <summary>
/// ������`�悷��N���X
/// </summary>
class Text
{

	//////////////////////////�摜���/////////////////////////////

	int hPict_;                     //�摜�ԍ�
	unsigned int width_, height_;	//1�������̕��ƍ���
	char fileName_[MAX_PATH];       //�����̉摜
	unsigned int rowLength_;        //�摜�̒��ɉ���������ł��邩

	//////////////////////////�\��/////////////////////////////

	float speed_;      //�����̕\������Ԋu�̑��x
	int fpsCount_;     //�t���[���̃J�E���g
	int totalDrawNum_; //�`�悵�Ă�������

public:
	Text();
	~Text();

	/// <summary>
	/// �������i�f�t�H���g�̐ݒ�j
	/// </summary>
	/// <returns>�����^���s</returns>
	HRESULT Initialize(float speed = 1.0f);

	/// <summary>
	/// �������i�I���W�i���̉摜���g���������j
	/// </summary>
	/// <param name="fileName">�摜�t�@�C����</param>
	/// <param name="charWidth">�摜�̂P�����̕��i�s�N�Z���j</param>
	/// <param name="charHeight">�摜�̂P�����̍����i�s�N�Z���j</param>
	/// <param name="rowLength">�摜�̒��ɉ��ɉ���������ł��邩</param>
	/// <returns>�����^���s</returns>
	HRESULT Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength, float speed);

	/// <summary>
	/// �`��i������:�����j
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="str">�\��������������</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	void NumberDraw(int x, int y, const char* str, float ratio = 1.0f);

	/// <summary>
	/// �`��i������j�ꕶ�����Ƃɏ��X�ɕ\������
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="str">�\��������������</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	/// <param name="speed">�����̕\������Ԋu�̑��x</param>
	void SlowlyDraw(int x, int y, const char* str,float ratio = 1.0f);

	/// <summary>
	/// �`��i�����l�j
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="value">�\���������l</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	void NumberDraw(int x, int y, int value, float ratio = 1.0f);

	/// <summary>
	/// �`��i�����l�j�ꕶ�����Ƃɏ��X�ɕ\������
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="value">�\���������l</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	void SlowlyDraw(int x, int y, int value, float ratio = 1.0f);

	//���
	void Release();
};

