#pragma once
#include "../Engine/GameObject.h"

//��
class Bullet : public GameObject
{

	int hModel_;			//���f���ԍ�
	int lifeTimeCount_;		//�ǂ̂��炢�������Ă��邩
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

	//�R���C�_�[�ɓ����������ɌĂ΂��֐�
	void OnCollision(GameObject* pTarget) override;

	////////////////////////////�֐�/////////////////////////////

	//�m�b�N�o�b�N
	void KnockBack();

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// �O�x�N�g�����Z�b�g
	/// </summary>
	/// <param name="v">�Z�b�g�������O�x�N�g��</param>
	void SetFront(const XMVECTOR& v) { front_ = v; }
};

