#pragma once
#include "../Engine/GameObject/GameObject.h"
#include <stdio.h>

/// <summary>
/// ��Q����ݒu����N���X
/// </summary>
class MiniGameSetObject : public GameObject
{
	float radius_;           //�X�e�[�W�̔��a
	int fpsCount_;           //�ǂ̂��炢fps�������Ă��邩
	int generatingSpeed_;    //�����X�s�[�h

public:

	//�R���X�g���N�^
	MiniGameSetObject(GameObject* parent);

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

	/////////////////////////�֐�//////////////////////////

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	void ObjectGeneration();

	/// <summary>
	/// ����
	/// </summary>
	void Generation();

	//////////////////�����̎d���̊֐�/////////////////////

	void Center();       //�^��
	void Edge();         //�[
	void MultipleEdge(); //�����̂ɒ[

	/// <summary>
	///  �g�̐^�񒆂ɐ���
	/// </summary>
	/// <typeparam name="T">�N���X�ɂ���ĕ����邽��</typeparam>
	/// <param name="Class">��������N���X</param>
	template <class T>
	void Instantiate_Center(XMFLOAT3 pos);

	/// <summary>
	/// �g�̒[�ɐ���
	/// </summary>
	/// <typeparam name="T">�N���X�ɂ���ĕ����邽��</typeparam>
	/// <param name="Class">��������N���X</param>
	template <class T>
	void Instantiate_Edge(XMFLOAT3 pos);

	/// <summary>
	/// �g�̒[�ɕ����̐���
	/// </summary>
	/// <typeparam name="T">�N���X�ɂ���ĕ����邽��</typeparam>
	/// <param name="Class">��������N���X</param>
	template <class T>
	void Instantiate_Multiple_Edge(XMFLOAT3 pos);

};
