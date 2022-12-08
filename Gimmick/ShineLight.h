#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

class ShineLight : public Mob
{

	//�萔

	const int LIGHT_INTENSITY = 2;	 //���C�g�̋���
	const int REACTION_DISTANCE = 3; //��������

	//�ϐ�

	int lightNum_;    //���C�g�̔ԍ�
	float  num_;      //��
	bool shineFlag_;  //�����Ă��邩�ǂ���

public:

	//�R���X�g���N�^
	ShineLight(GameObject* parent, std::string modelPath, std::string name);

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;
};

