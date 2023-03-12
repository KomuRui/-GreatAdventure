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

	//���f���p�X�l�[��
	std::string modelPathName_;

	//���g���I������Ă��邩�ǂ���
	bool isSelect_;             

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
};

