#pragma once
#include "../../../Button/ButtonBase.h"


/// <summary>
/// �Q�[����ʂɖ߂�{�^��
/// </summary>
class BackButton : public ButtonBase
{

	int hSelectPict_;    //�I������Ă���Ƃ��̉摜�ԍ�
	int hNotSelectPict_; //�I������Ă��Ȃ��Ƃ��̉摜�ԍ�

public:

	//�R���X�g���N�^
	BackButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// �{�^���������ꂽ�牽���邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonPush() override;

	/// <summary>
	/// �{�^�����I�����ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelect() override;

	/// <summary>
	/// �{�^�����I���������ꂽ�u�Ԃɉ������邩
	/// </summary>
	/// <param name="p">���s�������֐��|�C���^</param>
	void IsButtonSelectRelease() override;
};