#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"
#include "Button.h"
#include "Engine/BoxCollider.h"

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

	//�����蔻��
	virtual void OnCollision(GameObject* pTarget) override {};

	//�p���悲�Ƃ�Update�ł̓�������ς���
	virtual void UpdateMove();

	//�p����p�̏�����
	virtual void ChildInitialize();

	//�p����p�̕`��
	virtual void ChildDraw();

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	virtual void ChildStartUpdate();

};

//�R�C���N���X
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath) :Mob(parent, modelPath) {}

	//�R�C���̓�����
	void UpdateMove() override;

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;
};

//���[�v�N���X
class Warp : public Mob
{
public:

	//�R���X�g���N�^
	Warp(GameObject* parent, std::string modelPath) :Mob(parent, modelPath)
	{
		BoxCollider* collision = new BoxCollider(XMFLOAT3(0, -2, 0), XMFLOAT3(5.5, 4, 5.5));
		AddCollider(collision);
	}

	//���[�v�̓�����
	void UpdateMove() override 
	{ 
		transform_.rotate_.y += 2;

		if (transform_.rotate_.y > 360)
			transform_.rotate_.y = 0;
	}

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			XMFLOAT3 pos = transform_.position_;
			pos.y += 1;
			pTarget->SetPosition(pos);
		}
	}

};

