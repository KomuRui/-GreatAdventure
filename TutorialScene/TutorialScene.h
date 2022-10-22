#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Fade.h"
#include "../Button.h"

//�����V�[�����Ǘ�����N���X
class TutorialScene : public GameObject
{
	//TutorialScene�ɕ\������摜
	enum TitleImages
	{
		TITLE = 0,
		START,
		MAX_SIZE_TITLEIMAGE
	};

	int hPict_[MAX_SIZE_TITLEIMAGE];    //�摜�ԍ�

	Fade* pfade_;				        //�t�F�[�h�p


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TutorialScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void StartUpdate() override;
};

