#pragma once
#include "Block.h"

//�A�C�e���u���b�N�N���X
class ItemBlock : public Block
{
	int status_;

public:

	//�R���X�g���N�^
	ItemBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name), status_(0){}

	//�A�b�v�f�[�g
	void BlockChildUpdate() override
	{
		if (status_ == 1) move();
	}

	//�u���b�N�̓���
	void move()
	{
		Angle += 0.05;
	}

	//��ԃZ�b�g
	void SetStatus(const int& num)
	{
		status_ = num;
	}
};
