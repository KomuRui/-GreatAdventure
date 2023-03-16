#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �G���h���[���������V�[��
/// </summary>
class EndRolesScene : public GameObject
{
	//���y�ԍ�
	int hAudio_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EndRolesScene(GameObject* parent);

	//�f�X�g���N�^
	~EndRolesScene();

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};


