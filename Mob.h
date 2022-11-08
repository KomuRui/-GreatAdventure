#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"

//�����V�[�����Ǘ�����N���X
class Mob : public GameObject
{
protected:

	//���f���ԍ�
	int hModel_;

	//�t�@�C���l�[���p�X
	std::string ModelNamePath_;

	//�R���W�����̎g�p
	enum Collision
	{
		No,
		Box,
		Sphere,
	};

	//�ǂ̃R���W�������g����
	int colliderState; 

	//�����蔻��̊e���
	XMFLOAT3 pos;  //���S�ʒu
	XMFLOAT3 size; //�傫��
	int     radius;//���a

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mob(GameObject* parent,std::string modelPath, std::string name);

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
	virtual void UpdateMove() {};

	//�p����p�̏�����
	virtual void ChildInitialize() {};

	//�p����p�̕`��
	virtual void ChildDraw() {};

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	virtual void ChildStartUpdate() {};

	//�p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	virtual void OnCollision(GameObject* pTarget) override { int a = 0; }

};

//�R�C���N���X
class Coin : public Mob
{
public:

	//�R���X�g���N�^
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}


	void ChildInitialize() override
	{
		BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1 * transform_.scale_.y, 0), XMFLOAT3(2 * transform_.scale_.x, 2 * transform_.scale_.y, 2 * transform_.scale_.z));
		AddCollider(collision);

		SetEmission();
	}

	//�R�C���̓�����
	void UpdateMove() override
	{
		transform_.rotate_.y += 4;
	}

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		if (pTarget->GetObjectName() == "Player")
		{
			KillMe();
		}
	}
};

//���[�v�N���X
class Warp : public Mob
{
private:

	//�萔
	const float    ROTATION_QUANTITY = 1.0f;        //��]��
	const float    ADDITION_TURNOVERRATE = 0.01f;   //��]�������Z�����
	const float    MAX_TURNOVERRATE = 10.0f;        //�ő��]��
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };     //�R���C�_�[�|�W�V����
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 }; //�R���C�_�[�T�C�Y

	//�ϐ�
	float    turnoverRate_;  //��]��
	int      status_;        //���
	XMFLOAT3 playerPos_;     //���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�

	//���[�v�ɏ��
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

public:

	//�R���X�g���N�^
	Warp(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(Stop)
		,turnoverRate_(1), playerPos_(0,0,0)
	{}

	//������
	void ChildInitialize() override
	{
		//���g�ɓ����蔻���ǉ�
		BoxCollider* collision = new BoxCollider(COLLIDER_POS, COLLIDER_SIZE);
		AddCollider(collision);

		//���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
		playerPos_ = { transform_.position_.x,transform_.position_.y - 1.0f,transform_.position_.z };
	}

	//���[�v�̓�����
	void UpdateMove() override 
	{ 
		//Y����]������
		transform_.rotate_.y += ROTATION_QUANTITY * turnoverRate_;

		//Y���̊p�x��360���傫���Ȃ�0�ɖ߂�
		if(transform_.rotate_.y > TWOPI_DEGREES) transform_.rotate_.y = ZEROPI_DEGREES;
	}

	//�����蔻��
	void OnCollision(GameObject* pTarget) override
	{
		//Player�ƏՓ˂�����
		if (pTarget->GetObjectName() == "Player")
		{
			//Player�|�W�V�������Z�b�g����
			pTarget->SetPosition(playerPos_);

			//Player�Ɠ������Ă����ԂȂ��]�����ǂ�ǂ񑁂߂�
			//������]�����ő�܂ŒB�������Ԃ�Move�ɐݒ�
			(turnoverRate_ < MAX_TURNOVERRATE ? turnoverRate_ += ADDITION_TURNOVERRATE : status_ = Move);
		}
	}

};

