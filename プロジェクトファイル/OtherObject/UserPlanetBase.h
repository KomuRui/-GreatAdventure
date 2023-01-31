#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// ���̏��
/// </summary>
enum class PlanetStatus
{
	Stop,      //��~
	Move,      //�ړ�
	Fall,      //������
	MAX_STATUS
};

/// <summary>
/// ���[�U�[�̐��̃x�[�X�N���X
/// </summary>
class UserPlanetBase : public GameObject
{
protected:

	////�ϐ�

	int hModel_; 				//���f���ԍ��i�[�p
	PlanetStatus status_;       //���
	std::string ModelNamePath_; //�t�@�C���l�[���p�X
	XMFLOAT3 nextPos_;          //���̃|�W�V����
	bool isSelect_;             //���g���I������Ă��邩�ǂ���

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

	/// <summary>
	/// ���̈ʒu�ֈړ�
	/// </summary>
	void NextPositionToMove();

	/// <summary>
	/// ���̃|�W�V�����Z�b�g
	/// </summary>
	/// <param name="nextPos">���̃|�W�V����</param>
	void SetNextPosition(const XMFLOAT3& nextPos); 

	/// <summary>
	/// �I������Ă��Ȃ��̂Ȃ痎����
	/// </summary>
	void Fall();

	/// <summary>
	/// ��Ԃ��Z�b�g
	/// </summary>
	/// <param name="status">�Z�b�g���������</param>
	/// <returns>true�Ȃ��Ԃ�ύX����</returns>
	bool SetStatus(PlanetStatus status);

	/// <summary>
	/// ��Ԃ��Q�b�g
	/// </summary>
	/// <returns>���</returns>
	PlanetStatus GetStatus() { return status_; }

	/// <summary>
	/// �I������Ă��邩�ǂ���
	/// </summary>
	/// <returns>true�Ȃ�I������Ă���</returns>
	bool IsSelect();

	/// <summary>
	/// �I������Ă��邩�ǂ����Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�I������Ă���,false�Ȃ炳��Ă��Ȃ�</param>
	void SetIsSelect(const bool& flag);
};

