#pragma once
#include "../../../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class WorldScene1 : public GameObject
{

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	WorldScene1(GameObject* parent);

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
