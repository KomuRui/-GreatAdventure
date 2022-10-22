#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	//���f���ԍ�
	int hModel_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//���f���ԍ��̃Q�b�g�֐�
	int GethModel() { return hModel_; }
};

