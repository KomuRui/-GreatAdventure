#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �~�j�Q�[���V�[��
/// </summary>
class MiniGameScene : public GameObject
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MiniGameScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

