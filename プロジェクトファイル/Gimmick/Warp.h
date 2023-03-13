#pragma once
#include "../Mob/Mob.h"
#include "../Player/PlayerBase.h"
#include "../Engine/GameObject/PolyLine.h"
#include "../Manager/SceneManager/SceneManager.h"

/// <summary>
/// ���[�v�̌^(���̃N���X�ł��Q�Ƃ������̂ŊO�ɏo��)
/// </summary>
enum WarpType
{
	Normal = 0,
	InverseNormalAndDown,
	MoveToPurpose
};

/// <summary>
/// Player�����̐��ɍs�����߂ɕK�v�ȃ��[�v�N���X
/// </summary>
class Warp : public Mob
{
private:

	//���[�v�̏��
	enum WarpStatus
	{
		STOP,
		MOVE,
		MAX_WARP_STATUS
	};

	//�ϐ�
	float    turnoverRate_;		//��]��
	int      status_;			//���
	int      type_;		    	//���[�v�̌^
	int      stageReleaseNum_;  //�X�e�[�W����̐�(HomeScene�ɖ߂�Ƃ��Ɏg������)  
	XMFLOAT3 playerPos_;        //���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	PolyLine* pRightLine_;      //���[�v�̃G�t�F�N�g�E��
	PolyLine* pLeftLine_;       //���[�v�̃G�t�F�N�g����
	PolyLine* pBaseLine_;       //���[�v�̃G�t�F�N�g�E��
	XMFLOAT3 warpTarget_;	    //���[�v�̈ړ���
	SCENE_ID id_;				//�V�[���J�ڂ�ID

public:

	//�R���X�g���N�^
	Warp(GameObject* parent, std::string modelPath, std::string name);

	//�f�X�g���N�^
	~Warp();

	//������
	void ChildInitialize() override;

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	//�p����p�̕`��
	void ChildDraw() override;

	//�p����p�̊J��
	void ChildRelease() override;

	/// <summary>
	/// ���̐��܂ňړ�
	/// </summary>
	void MovingToStar();

	/// <summary>
	/// ���̖ړI�n�܂ňړ�
	/// </summary>
	void MovingToPurpose();

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="pTarget">������������̃|�C���^</param>
	void OnCollision(GameObject* pTarget) override;

	/// <summary>
	/// ���[�v�̌^�Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g�������^</param>
	void SetWarpType(const int& type) { type_ = type; }

	/// <summary>
	/// ���[�v�̈ړ���ݒ�
	/// </summary>
	/// <param name="target"></param>
	void SetWarpTarget(const XMFLOAT3& target) { warpTarget_ = target; }

	/// <summary>
	/// �@�����Z�b�g
	/// </summary>
	/// <param name="nor">�Z�b�g�������@��</param>
	void SetNormal(const XMVECTOR& nor) { vNormal_ = nor; }

	/// <summary>
	/// �V�[���̑J�ڐ�ID���Z�b�g
	/// </summary>
	/// <param name="id">�Z�b�g�������V�[���̑J�ڐ�ID</param>
	void SetSceneId(const SCENE_ID& id) { id_ = id; }

	/// <summary>
	/// ����X�e�[�W���Z�b�g
	/// </summary>
	void SetStageRelease(const int& num) { stageReleaseNum_ = num; }
};

