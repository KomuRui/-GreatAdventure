#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Time.h"

//�O��`
class CreateStage;

/// <summary>
/// ���[�U���Q�[���X�^�[�g���鎞��UI
/// </summary>
class UserGameStartUI : public GameObject
{
	//UI�Ƃ��\������p
	CreateStage* pCreateStage_;

public:

	//�R���X�g���N�^
	UserGameStartUI(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override {};

	//�J��
	void Release() override {};
};

