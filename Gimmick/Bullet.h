#pragma once
#include "../Engine/GameObject.h"

//��
class Bullet : public GameObject
{
	////�萔

	const int LIFE_TIME = 180;                   //��������
	const XMFLOAT3 COLLIDER_POS = { 0,0,0 };     //�R���C�_�[�̈ʒu
	const float    COLLIDER_SIZE = 2.0f;         //�R���C�_�[�̃T�C�Y

	////�ϐ�
	
	int hModel_;			//���f���ԍ�
	int lifeTimeCount_;		//�ǂ̂��炢�������Ă��邩
	float speed_;			//���̃X�s�[�h
	XMVECTOR front_;		//�O�x�N�g��


public:

	//�R���X�g���N�^
	Bullet(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;
	
	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	//�O�x�N�g���Z�b�g����
	void SetFront(const XMVECTOR& v) { front_ = v; }
};

