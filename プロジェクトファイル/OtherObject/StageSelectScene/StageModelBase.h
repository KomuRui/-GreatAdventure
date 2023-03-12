#pragma once
#include "../../Engine/GameObject/GameObject.h"


/// <summary>
/// �X�e�[�W��I�����鎞�̃X�e�[�W���f���̃x�[�X�ƂȂ�N���X
/// </summary>
class StageModelBase : public GameObject
{
protected:

	//���f���ԍ�
	int hModel_;

	//�摜�ԍ�
	int hPict_;

	//�摜��transform
	Transform tPict_;

	//���f���p�X�l�[��
	std::string modelPathName_;

	//���g���I������Ă��邩�ǂ���
	bool isSelect_;             

	//�X�e�[�W���������Ă��邩�ǂ���
	bool isStageRelease_;

public:

	//�R���X�g���N�^
	StageModelBase(GameObject* parent, std::string ModelPath, std::string name);

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

	/// <summary>
	/// �I������Ă��鎞�Ƀ{�^�������������̏���
	/// </summary>
	virtual void SelectButtonPush() {};

	/// <summary>
	/// �������Ă��Ȃ��X�e�[�W�̎��Ƀ{�^�������������̏��u
	/// </summary>
	virtual void NotStageReleaseButtonPush();

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
	/// �I������Ă��邩�Z�b�g
	/// </summary>
	/// <param name="flag">true�Ȃ�Z�b�g����Ă���</param>
	void SetSelect(bool flag) { isSelect_ = flag; }
};

