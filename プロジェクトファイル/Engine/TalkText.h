#pragma once
#include "Text.h"

/// <summary>
/// ���u���b���Ƃ��Ɏg���N���X
/// </summary>
class TalkText
{
	//�\�����镶��
	std::string text_;

public:

	//�R���X�g���N�^
	TalkText() {};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="text">�\��������������</param>
	void Initialize(std::string text);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};

