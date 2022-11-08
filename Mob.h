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

