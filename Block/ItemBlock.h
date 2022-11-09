#pragma once
#include "../Mob.h"

//�A�C�e���u���b�N�N���X
class ItemBlock : public Mob
{
	int status_;

public:

	//�R���X�g���N�^
	ItemBlock(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(0){}

	//�A�b�v�f�[�g
	void UpdateMove() override
	{
		if (status_ == 1) move();
	}

	//�u���b�N�̓���
	void move()
	{
		Angle += 0.05;
	}

	//��ԃZ�b�g
	void SetStatus(int num)
	{
		status_ = num;
	}
};
