#pragma once
#include "Engine/GameObject.h"
#include "Engine/BoxCollider.h"
#include "Engine//SphereCollider.h"
#include "Engine/Global.h"
#include "Stage.h"
#include "Engine/Particle.h"

//�����V�[�����Ǘ�����N���X
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

	//�X�e�[�W�ɍ��킹��Mob����]
	void RotationInStage();

	//�p���悲�Ƃ�Update�ł̓�������ς���
	virtual void ChildUpdate() {};

	//�p����p�̏�����
	virtual void ChildInitialize() {};

	//�p����p�̕`��
	virtual void ChildDraw() {};

	//�p����p�̃X�^�[�g�A�b�v�f�[�g
	virtual void ChildStartUpdate() {};

	//�p����p�̊J��
	virtual void ChildRelease() {};

	//�p����p�̃R���C�_�[�����������ɌĂ΂��֐�
	virtual void OnCollision(GameObject* pTarget) override {};

	//�p����p�̎w�肵�����ԂŌĂ΂�郁�\�b�h
	virtual void TimeMethod() override {};
};

