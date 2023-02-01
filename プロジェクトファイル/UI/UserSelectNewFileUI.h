#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

class CreateStage;

/// <summary>
/// ���[�U�[���I���V�[���̐V�����t�@�C�����쐬���鎞��UI
/// </summary>
class UserSelectNewFileUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

public:

	//�R���X�g���N�^
	UserSelectNewFileUI(GameObject* parent);

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
};

