#pragma once
#include "../Mob.h"
#include "../Player.h"
#include "../Engine/PolyLine.h"
#include "../Engine/SceneManager.h"

//���[�v�N���X
class Warp : public Mob
{
private:

	//���[�v�ɏ��
	enum WarpStatus
	{
		STOP,
		MOVE,
		MAX_WARP_STATUS
	};

	//�|�����C�����o���Ƃ���
	enum PolyLineNumber
	{
		RIGHT,
		LEFT,
		BASE,
		MAX_POLY_LINE
	};

	//�萔
	const int      FADE_OUT_DISTANCE = 600;          //�t�F�[�h�A�E�g���鎞�̋���
	const int      SCENE_MOVE_DISTANCE = 300;        //�V�[���ڍs���鎞�̋���
	const float    ROTATION_QUANTITY = 0.02f;        //��]��
	const float    ADDITION_TURNOVERRATE = 0.03f;    //��]�������Z�����
	const float    MAX_TURNOVERRATE = 10.0f;         //�ő��]��
	const XMFLOAT3 COLLIDER_POS = { 0, -2, 0 };      //�R���C�_�[�|�W�V����
	const XMFLOAT3 COLLIDER_SIZE = { 5.5, 4, 5.5 };  //�R���C�_�[�T�C�Y

	//�ϐ�
	float    turnoverRate_;			 //��]��
	int      status_;				 //���
	int      number_;				 //���[�v�̔ԍ�
	XMFLOAT3 playerPos_;			 //���[�v��Player���悹��Ƃ���Player�̃|�W�V������ݒ�
	PolyLine* pLine[MAX_POLY_LINE];  //���[�v�̃G�t�F�N�g
	XMFLOAT3 warpTarget_;			 //���[�v�̈ړ���
	SCENE_ID id_;					 //�V�[���J�ڂ�ID

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

	//���̐��܂ňړ�
	void MovingToStar();

	//���̖ړI�n�܂ňړ�
	void MovingToPurpose();

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;

	//���[�v�̔ԍ��Z�b�g
	void SetNumber(const int& num) { number_ = num; }

	//���[�v�̈ړ���ݒ�
	void SetWarpTarget(const XMFLOAT3& target) { warpTarget_ = target; }

	//�@�����Z�b�g
	void SetNormal(const XMVECTOR& nor) { vNormal = nor; }

	//�V�[���J�ڐ��ID���Z�b�g
	void SetSceneId(const SCENE_ID& id) { id_ = id; }
};

