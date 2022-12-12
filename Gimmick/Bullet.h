#pragma once
#include "../Engine/GameObject.h"

//��
class Bullet : public GameObject
{
	////�萔

	//��������
	const int LIFE_TIME = 180;

	////�ϐ�
	
	//���f���ԍ�
	int hModel_;

	//�ǂ̂��炢�������Ă��邩
	int lifeTimeCount_;

	//���̃X�s�[�h
	float speed_;

	//�O�x�N�g��
	XMVECTOR front_;


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

