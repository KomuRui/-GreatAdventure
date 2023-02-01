#pragma once
#include "ButtonBase.h"

/// <summary>
/// �V�����t�@�C�����Ƃ��̃L�����Z���{�^��
/// </summary>
class NewFileCancelButton : public ButtonBase
{

	//�I������Ă��Ȃ��Ƃ��̉摜�ԍ�
	int hNotSelectPict_;

public:

	//�R���X�g���N�^
	NewFileCancelButton(GameObject* parent, std::string modelPath, std::string name);

	/// <summary>
	/// �I���摜��ݒ�
	/// </summary>
	void SetSelectImage();

	/// <summary>
	/// �I������Ă��Ȃ��Ƃ��̉摜��ݒ�
	/// </summary>
	void SetNotSelectImage();

	/// <summary>
	/// �߂�
	/// </summary>
	void Back();

	/// <summary>
	/// �A�C�R���I����
	/// </summary>
	void GoIconSelect();
};

