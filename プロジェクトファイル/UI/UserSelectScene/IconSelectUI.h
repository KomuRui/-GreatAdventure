#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Time.h"

//�O��`
class CreateStage;
class EasingMove;

/// <summary>
/// ���[�U�[���I���V�[���̃A�C�R����I�����鎞��UI
/// </summary>
class IconSelectUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

	//UI���C�[�W���O�ňړ�������p
	EasingMove* pEasingMove_;

	//�A�C�R���̃��f���p�X
	std::string iconModelPath_;

	//�C�[�W���O�ύX�������ǂ���
	bool isEasingChange_;

	//�{�^�������̂������邩
	bool isButtonPushOk_;

public:

	//�R���X�g���N�^
	IconSelectUI(GameObject* parent);

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
	/// �C�[�W���O�̓������ύX
	/// </summary>
	/// <param name="path">�A�C�R���̃��f���p�X</param>
	void ChangeEasingMove(std::string path);

	/// <summary>
	/// �{�^�������̂������邩�擾
	/// </summary>
	/// <returns>true�Ȃ狖��</returns>
	bool IsButtonPushOk() { return isButtonPushOk_; }
};

