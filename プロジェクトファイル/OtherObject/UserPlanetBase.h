#pragma once
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/Component/EasingMove.h"
#include "../Engine/ResourceManager/Text.h"

/// <summary>
/// ���̏��
/// </summary>
enum class PlanetStatus
{
	Stop,          //��~
	Move,          //�ړ�
	Fall,          //������
	Explosion,     //����
	ReturnPosition,//���̈ʒu�ɖ߂�
	MAX_STATUS
};

/// <summary>
/// ���[�U�[�̐��̃x�[�X�N���X
/// </summary>
class UserPlanetBase : public GameObject
{
protected:

	//���[�U���
	void(*UserCreateNewFile)(std::string);  //���[�U����V�K�o�^���鎞�ɌĂԊ֐�

	//���f��
	int hModel_; 				//���f���ԍ��i�[�p
	std::string ModelNamePath_; //�t�@�C���l�[���p�X

	//�摜
	int hNewFilePict_;          //�V�K�쐬�摜�ԍ�
	int hCoinPict_;             //�R�C���摜
	int hStagePict_;            //�X�e�[�W�摜
	int hCrossPict_;            //�~�摜
	
    //���
	PlanetStatus status_;      

	//���̑�
	Text* pText_;			    //�R�C���̐��\������p
	EasingMove* pEasingRotate_; //��]�C�[�W���O�p
	EasingMove* pEasingMove_;   //�ړ��C�[�W���O�p
	XMFLOAT3 nextPos_;          //�ړ�����Ƃ��̎��̃|�W�V����
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

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
    void TimeMethod() override;

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
	/// �������ă��f���ύX
	/// </summary>
	void Explosion();

	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	void ExplosionEffect();

	/// <summary>
	/// �V�K�쐬
	/// </summary>
	void CreateNewFile();

	/// <summary>
	/// ���̈ʒu�ɖ߂�
	/// </summary>
	void ReturnPosition();

	/// <summary>
	/// �C�[�W���O�ړ����Z�b�g
	/// </summary>
	void SetEasingMove();

	/// <summary>
	/// �߂�C�[�W���O�ړ����Z�b�g
	/// </summary>
	void SetReturnEasingMove();

	/// <summary>
	/// ��Ԃ��Z�b�g
	/// </summary>
	/// <param name="status">�Z�b�g���������</param>
	void SetStatus(PlanetStatus status,std::string iconModelPath = "");

	/// <summary>
	/// �������ԂɕύX
	/// </summary>
	/// <returns>true�Ȃ��Ԃ�ύX����</returns>
	bool SetFallStatus();

	/// <summary>
	/// ��Ԃ��Q�b�g
	/// </summary>
	/// <returns>���</returns>
	PlanetStatus GetStatus() { return status_; }

	/// <summary>
	/// �I������Ă��邩�ǂ���(�I������Ă�����I����ԉ���)
	/// </summary>
	/// <returns>true�Ȃ�I������Ă���</returns>
	bool IsSelectToChange();

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

	/// <summary>
	/// �����t�@�C�����ǂ���
	/// </summary>
	/// <returns>true�Ȃ�����t�@�C��</returns>
	bool IsExisting();
};

