#pragma once
#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/ResourceManager/Text.h"

/// <summary>
/// ���[�U�[���I���V�[����UI(�摜�Ƃ�����)
/// </summary>
class UserSelectSceneUI : public GameObject
{
	//�V�[���̖��O��\������e�L�X�g
	Text* sceneNameText;

public:

	//�R���X�g���N�^
	UserSelectSceneUI(GameObject* parent);

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

