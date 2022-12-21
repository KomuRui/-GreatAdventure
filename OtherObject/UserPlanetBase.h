#pragma once
#include "../Engine/GameObject.h"

//���[�U�[�̐��̃x�[�X�N���X
class UserPlanetBase : public GameObject
{
	//���
	enum Status
	{
		Stop,
		Move,
		MAX_STATUS
	};

	////�萔

	const float RATATION_SPEED = 0.1f;    //��]���x

	////�ϐ�

	int hModel_; 				//���f���ԍ��i�[�p
	int status_;                //���
	std::string ModelNamePath_; //�t�@�C���l�[���p�X
	XMFLOAT3 nextPos_;          //���̃|�W�V����

public:

	//�R���X�g���N�^
	UserPlanetBase(GameObject* parent, std::string modelPath, std::string name);

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

	/////////////////////�p����p�̊֐�//////////////////////

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

	/////////////////////�֐�//////////////////////

	//���̈ʒu�ֈړ�
	void NextPositionToMove();

	//���̃|�W�V�����Z�b�g
	void SetNextPosition(const XMFLOAT3& nextPos) { nextPos_ = nextPos; }
};

