#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �X�e�[�W�I���̃V�[��
/// </summary>
class StageSelectScene : public GameObject
{

	int hAudio_;    //���ԍ�

public:

	//�R���X�g���N�^
	StageSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~StageSelectScene();

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ�x�����Ă΂��
	void StartUpdate() override {};

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override {};

};

