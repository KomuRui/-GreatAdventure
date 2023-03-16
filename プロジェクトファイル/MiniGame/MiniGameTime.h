#pragma once
#include "../Engine/ResourceManager/Text.h"
#include "../Engine/ResourceManager/Time.h"

/// <summary>
/// �~�j�Q�[���̎��Ԃ�X�^�[�g���鎞�̃J�E���g��\��
/// </summary>
class MiniGameTime
{	

	Text* pTimeText_;           //���ԕ\�����邽�߂̕ϐ�
	Text* pStartCountText_;     //�X�^�[�g����܂ł̃J�E���g��\�����邽�߂̕����\���ϐ�

	int timerhNum_;             //�^�C�}�[�̃n���h���ԍ�
	int startCount_;            //�X�^�[�g����܂ł̃J�E���g
	float startCountTextScale_; //�X�^�[�g�J�E���g�����̊g�嗦

	bool isFinish_;             //�I���������ǂ���

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
	/// �������ԕ`��
	/// </summary>
	void LimitTimeDraw();

	/// <summary>
	/// �X�^�[�g�J�E���g�`��
	/// </summary>
	void StartCountDraw();

	/// <summary>
	/// �o�ߎ��Ԃ��Q�b�g
	/// </summary>
	float GetTime() { return Time::GetTimef(timerhNum_); }
};

