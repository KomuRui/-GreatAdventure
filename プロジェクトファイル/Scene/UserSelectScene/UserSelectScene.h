#pragma once
#include "../../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class UserSelectScene : public GameObject
{

	int hModel_; 	//���f���ԍ��i�[�p

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UserSelectScene(GameObject* parent);

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