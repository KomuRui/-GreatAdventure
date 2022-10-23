#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class Mob : public GameObject
{
	//���f���ԍ�
	int hModel_;

	//�t�@�C���l�[���p�X
	std::string ModelNamePath_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mob(GameObject* parent,std::string modelPath);

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

};

