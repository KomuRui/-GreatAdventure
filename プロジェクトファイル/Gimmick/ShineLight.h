#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

class ShineLight : public Mob
{

	//�萔

	const int LIGHT_INTENSITY = 2;	 //���C�g�̋���
	const int REACTION_DISTANCE = 4; //��������

	//�ϐ�

	int lightNum_;        //���C�g�̔ԍ�
	float  num_;          //��
	bool shineFlag_;      //�����Ă��邩�ǂ���
	bool shinePermitFlag_;//����̂������邩�ǂ���

public:

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//�X�^�[�g�A�b�v�f�[�g
	void ChildStartUpdate() override;

	//���[�v�̓�����
	void ChildUpdate() override;

	//�w�肵�����ԂŌĂ΂�郁�\�b�h
	void TimeMethod() override;

	////////////////////�֐�//////////////////////
 
	//�R���X�g���N�^
	ShineLight(GameObject* parent, std::string modelPath, std::string name);

	////////////////////�Z�b�^�[�Q�b�^�[//////////////////////
	
	//����Ȃ��悤�ɃZ�b�g
	void SetNotShineLight();

	//���点�邩���点�Ȃ������Z�b�g
	void SetShineFlag(const bool& flag) { shineFlag_ = flag; }

	//�����Ă��邩�ǂ����Q�b�g����
	bool GetShineFlag() { return shineFlag_; }

};

