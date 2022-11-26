#pragma once
#include "Engine/GameObject.h"
#include <vector>

//�O���錾
class Block;

//�e�X�e�[�W�N���X�̂��ƂƂȂ�N���X
class Stage : public GameObject
{
protected:

	//���f���̎��
	enum StageCategory
	{
		Base,   //�X�e�[�W�̃��f��
		Space,  //�w�i�̉F�����f��
		MAX
	};

	//�w�i���f��
	int spaceModel_;

	//�w�i���f���̃g�����X�t�H�[��
	Transform tSpace_;

	//�X�e�[�W��鎞�̖��O
	std::string StageFileNmae_[MAX];

	//�X�e�[�W���Ƃ̉�p
	int fieldAngle_[MAX];

	//�X�e�[�W���Ƃ̃��C�g�̋���
	int lightIntensity_[MAX];

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

	//�u���b�N��ۑ����Ă���Vector(��Ƀu���b�N�Ƃ̓����蔻����s�����߂Ɏg��)
	std::vector<Block*> tBlock_;

public:
};

