#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Fade.h"
#include "../../Button.h"

//�����V�[�����Ǘ�����N���X
class TutorialScene1 : public GameObject
{

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

