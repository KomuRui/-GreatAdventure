#pragma once
#include "../../Engine/GameObject.h"

/// <summary>
/// �`���[�g���A���V�[��1
/// </summary>
class TutorialScene1 : public GameObject
{

	int hAudio_; //���ԍ�

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TutorialScene1(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void StartUpdate() override;
};

