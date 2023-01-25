#pragma once
#include "../Engine/Text.h"


/// <summary>
/// �~�j�Q�[���̎��Ԃ�X�^�[�g���鎞�̃J�E���g��\��
/// </summary>
class MiniGameTime
{	

	Text* pTimeText_;           //���ԕ\�����邽�߂̕ϐ�
	Text* pStartCountText_;     //�X�^�[�g����܂ł̃J�E���g��\�����邽�߂̕����\���ϐ�

	int startCount_;            //�X�^�[�g����܂ł̃J�E���g
	float startCountTextScale_; //�X�^�[�g�J�E���g�����̊g�嗦

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MiniGameTime();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �������ԕ`��
	/// </summary>
	void LimitTimeDraw();

	/// <summary>
	/// �X�^�[�g�J�E���g�`��
	/// </summary>
	void StartCountDraw();
};

