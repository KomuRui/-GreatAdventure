#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �Ō�̂��P�l�Əo�Movie�𗬂��V�[��
/// </summary>
class LastScene : public GameObject
{

	int hAudio_; //���ԍ�

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	LastScene(GameObject* parent);

	//�f�X�g���N�^
	~LastScene();

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

