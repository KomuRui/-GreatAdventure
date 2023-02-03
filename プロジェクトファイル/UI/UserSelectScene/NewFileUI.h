#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Time.h"

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

	//�C�[�W���O�ύX�������ǂ���
	bool isEasingChange_;

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
	/// �C�[�W���O�̓������ύX
	/// </summary>
	void ChangeEasingMove();
};

