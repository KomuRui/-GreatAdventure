#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class TutorialStage : public GameObject
{
	//�X�e�[�W��ނ̐�
	enum StageCategory
	{
		first,
		Two,
		Three,
		MAX
	};

	//���f���ԍ�
	int hModel_[MAX];

	//�X�e�[�W���Ƃ�Player�̏����ʒu
	XMFLOAT3 pos_[MAX];

	//���݂ǂ��̃X�e�[�W��\�����Ă邩�̃X�e�[�^�X
	int status_;

	//���̂̃��f�����g�p���Ă��邩�ǂ���
	bool Circleflag_[MAX];

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TutorialStage(GameObject* parent);

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

	//���f���ԍ��̃Q�b�g�֐�
	int GethModel() { return hModel_[status_]; }

	//Pos�̃Q�b�g�֐�
	XMFLOAT3 GetPos() { return pos_[status_]; }

	//���̂̃��f�����g���Ă��邩�ǂ���
	bool GetCircleModel() { return Circleflag_[status_]; }
};

