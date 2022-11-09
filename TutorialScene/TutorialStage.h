#pragma once
#include "../Engine/GameObject.h"
#include <vector>

//�����V�[�����Ǘ�����N���X
class TutorialStage : public GameObject
{
	//�X�e�[�W��ނ̐�
	enum StageCategory
	{
		first,
		Two,
		MAX
	};

	//�w�i���f��
	int spaceModel_;

	//�w�i���f���̃g�����X�t�H�[��
	Transform tSpace_;

	//���f���ԍ�
	int hModel_[MAX];

	//���̂ɕ��̂��悹�邽�߂ɋ^�����f��
	int CirclePolyModel_;

	//�X�e�[�W���Ƃ�Player�̏����ʒu
	XMFLOAT3 pos_[MAX];

	//���݂ǂ��̃X�e�[�W��\�����Ă邩�̃X�e�[�^�X
	int status_;

	//3D�̃��f�����g�p���Ă��邩�ǂ���
	bool threeDflag_[MAX];

	//�u���b�N�̃|�W�V������ۑ����Ă���Vector(��Ƀu���b�N�Ƃ̓����蔻����s�����߂Ɏg��)
	std::vector<Transform> tBlock_;

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

	//�����Ƀu���b�N�����邩�ǂ���,������������d�Ȃ��Ă��镪���炷
	//����:status 0:�E 1:�� 2:�� 3:�� 
	bool IsBlock(XMFLOAT3 *pos, int status);

	//���f���ԍ��̃Q�b�g�֐�
	int GethModel() { return hModel_[status_]; }

	//���̂ɕ��̂��悹�邽�߂ɋ^�����f���ԍ��̃Q�b�g�֐�
	int GetPolyModell() { return CirclePolyModel_; }

	//Pos�̃Q�b�g�֐�
	XMFLOAT3 GetPos() { return pos_[status_]; }

	//3D�̓���������������
	bool GetthreeDflag() { return threeDflag_[status_]; }

	//�X�e�[�W�̐؂�ւ�
	void StatusPlus() { status_++; }

};

