#pragma once
#include "../../Stage.h"

/// <summary>
/// ���[�U�[���I���V�[���̃X�e�[�W
/// </summary>
class UserSelectStage : public Stage
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UserSelectStage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

