#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �~�j�Q�[���V�[��
/// </summary>
class MiniGameScene : public GameObject
{

	int hAudio_;    //���ԍ�

public:

	//�R���X�g���N�^
	MiniGameScene(GameObject* parent);

	//�f�X�g���N�^
	~MiniGameScene();

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

