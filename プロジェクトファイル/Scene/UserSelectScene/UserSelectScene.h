#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// ���[�U�Z���N�g
/// </summary>
class UserSelectScene : public GameObject
{

	int hAudio_;    //���ԍ�

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UserSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~UserSelectScene();

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