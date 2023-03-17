#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/CreateStage.h"

/// <summary>
/// �|�[�YUI
/// </summary>
class PauseUI
{
	//�eUI�쐬�p
	CreateStage* pCreateUI_;

	//UI��`�悵�Ă��邩
	bool isDrawUI_;

public:

	//�R���X�g���N�^
	PauseUI();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// UI�쐬
	/// </summary>
	void CreateUI();

	/// <summary>
	/// ���ׂč폜
	/// </summary>
	void AllRelease();

	/// <summary>
	/// UI��`�悵�Ă��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ�`�悵�Ă���</returns>
	bool isDrawUI() { return isDrawUI_; }
};

