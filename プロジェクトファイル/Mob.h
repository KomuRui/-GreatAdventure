#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/GameManager.h"

/// <summary>
/// �n�`�ɍ��킹�ĉ�]���������I�u�W�F�N�g�̊��N���X(Mob,Enemy,Warp,Coin�Ȃ�...)
/// </summary>
class Mob : public GameObject
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////
	 
	XMMATRIX TotalMx;			     //�L�����̉����̂��܂܂ł̃}�g���N�X�̑����}�g���N�X

	XMVECTOR Up;                     //�L�����̏�x�N�g��
	XMVECTOR Down;		   	         //�L�����̉��x�N�g��
	XMVECTOR vNormal;                //�L�����̉��̃X�e�[�W�̖@��

	float Angle;                     //�L�����̏�̎��̊p�x

	int hModel_;                     //���f���ԍ�
	std::string ModelNamePath_;      //�t�@�C���l�[���p�X

	///////////////�����蔻��///////////////////

	Stage* pstage_;                 //�X�e�[�W�N���X�̃|�C���^
	int      hGroundModel_;         //�X�e�[�W�̃��f���ԍ�������ϐ�

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

	/// <summary>
	/// �X�e�[�W�ɍ��킹�ĉ�]
	/// </summary>
	void RotationInStage();

	/// <summary>
	/// ���g�̖@�����Z�b�g
	/// </summary>
	/// <param name="nor">�Z�b�g�������@��</param>
	void SetNormal(const XMVECTOR& nor) { vNormal = nor; }

	/// <summary>
	/// �L�����̏㎲���Z�b�g
	/// </summary>
	/// <param name="angle">�Z�b�g�������L�����̏㎲</param>
	void SetAngle(const float& angle) { Angle = angle; }

	/// <summary>
	/// ���f���p�X�l�[�����擾
	/// </summary>
	/// <returns>���f���p�X�l�[��</returns>
	std::string GetModelPathName() { return ModelNamePath_; }

	/// <summary>
	/// �p����p��Update
	/// </summary>
	virtual void ChildUpdate() {};

	/// <summary>
	/// �p����p�̏�����
	/// </summary>
	virtual void ChildInitialize() {};

	/// <summary>
	/// �p����p�̕`��
	/// </summary>
	virtual void ChildDraw() {};

	/// <summary>
	/// �p����p�̍X�V�̑O�Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void ChildStartUpdate() {};

	/// <summary>
	/// �p����p�̊J��
	/// </summary>
	virtual void ChildRelease() {};

	/// <summary>
	/// �p����p�̃R���C�_�[�ɓ����������ɌĂ΂��֐�
	/// </summary>
	/// <param name="pTarget">���������I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnCollision(GameObject* pTarget) override {};

	/// <summary>
	/// �p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	/// </summary>
	virtual void TimeMethod() override {};
};

