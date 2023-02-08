#pragma once
#include "../../Button/ButtonBase.h"

//�O��`
class EasingMove;

/// <summary>
/// ���[�U�I��ŃQ�[���X�^�[�g����Ƃ��̃L�����Z���{�^��
/// </summary>
class UserGameCancelButton : public ButtonBase
{

	int hSelectPict_;    //�I������Ă���Ƃ��̉摜�ԍ�
	int hNotSelectPict_; //�I������Ă��Ȃ��Ƃ��̉摜�ԍ�

	XMFLOAT3 easingBeforePos_; //�C�[�W���O�̈ړ��O�|�W�V����
	XMFLOAT3 easingAfterPos_;  //�C�[�W���O�̈ړ���|�W�V����

	EasingMove* pEasingMove_;  //UI���C�[�W���O�ňړ�������p

public:

	//�R���X�g���N�^
	UserGameCancelButton(GameObject* parent, std::string modelPath, std::string name);

	////////////////////�I�[�o�[���C�h����֐�/////////////////////////

	/// <summary>
	/// ������
	/// </summary>
	void ChildInitialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void ChildButtonUpdate() override;

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

