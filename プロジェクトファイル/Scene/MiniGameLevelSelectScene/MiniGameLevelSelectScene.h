#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �~�j�Q�[���̃��x����I������V�[��
/// </summary>
class MiniGameLevelSelectScene : public GameObject
{

	int hAudio_;    //���ԍ�

public:

	//�R���X�g���N�^
	MiniGameLevelSelectScene(GameObject* parent);

	//�f�X�g���N�^
	~MiniGameLevelSelectScene();

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

