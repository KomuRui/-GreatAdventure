#pragma once
#include "../Engine/GameObject.h"

class TitleStartImage : public GameObject
{
	//�g���摜�̎��
	enum type
	{
		Default,
		A_Select,
		RT_Select,
		All_Select,
		MAX_IMAGE_TYPE
	};

	////�萔

	const XMFLOAT3 BEFORE_SCALE = { 1.0,1.0,1.0 };
	const XMFLOAT3 AFTER_SCALE = { 1.1,1.1,1.1 };

	////�ϐ�

	int hPict_[MAX_IMAGE_TYPE];   //�摜�ԍ�
	std::string ModelNamePath_;   //�t�@�C���l�[���p�X

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleStartImage(GameObject* parent, std::string modelPath, std::string name);

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

