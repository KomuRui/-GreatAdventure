#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �`���[�g���A���V�[��2
/// </summary>
class TutorialScene2 : public GameObject
{

	int hAudio_; //���ԍ�

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TutorialScene2(GameObject* parent);

	//�f�X�g���N�^
	~TutorialScene2();

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

