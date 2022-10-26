#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class Mob : public GameObject
{
protected:

	//���f���ԍ�
	int hModel_;

	//�t�@�C���l�[���p�X
	std::string ModelNamePath_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mob(GameObject* parent,std::string modelPath);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�p���悲�Ƃ�Update�ł̓�������ς���
	virtual void UpdateMove();

};

//�R�C���N���X
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath) :Mob(parent, modelPath) {}

	//�R�C���̓�����
	void UpdateMove() override;
};

