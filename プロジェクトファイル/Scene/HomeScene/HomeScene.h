#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �X�e�[�W�ɍs���O��Player�̉Ƃ̃V�[��
/// </summary>
class HomeScene : public GameObject
{

	int hAudio_;    //���ԍ�

public:

	//�R���X�g���N�^
	HomeScene(GameObject* parent);

	//�f�X�g���N�^
	~HomeScene();

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

