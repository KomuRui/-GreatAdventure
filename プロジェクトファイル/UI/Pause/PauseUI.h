#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �|�[�YUI
/// </summary>
class PauseUI : public GameObject
{

private:

	//�R���X�g���N�^
	PauseUI(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override {};

	//�X�V
	void Update() override {};

	//�`��
	void Draw() override {};

	//�J��
	void Release() override {};

};

