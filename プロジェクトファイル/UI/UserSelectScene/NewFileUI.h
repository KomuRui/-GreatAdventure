#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Time.h"

//�O��`
class CreateStage;
class EasingMove;

/// <summary>
/// ���[�U�[���I���V�[���̐V�����t�@�C�����쐬���鎞��UI
/// </summary>
class NewFileUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

	//UI���C�[�W���O�ňړ�������p
	EasingMove* pEasingMove_;

	//�C�[�W���O�ύX���ăA�C�R���ɂ�����
	bool isEasingChangeIcon_;

	//�C�[�W���O�ύX���Č��ɖ߂�
	bool isEasingChangeReturn_;

	//�{�^�������̂������邩
	bool isButtonPushOk_;

public:

	//�R���X�g���N�^
	NewFileUI(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/// <summary>
	/// �C�[�W���O�̓������ύX���ăA�C�R����UI��
	/// </summary>
	void ChangeEasingMoveIcon();

	/// <summary>
	/// �C�[�W���O�̓������ύX���Č��Ƀ��f��
	/// </summary>
	void ChangeEasingMoveReturn();

	/// <summary>
	/// �{�^�������̂������邩�擾
	/// </summary>
	/// <returns>true�Ȃ狖��</returns>
	bool IsButtonPushOk() { return isButtonPushOk_; }
};

