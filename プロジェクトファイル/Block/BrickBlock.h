#pragma once
#include "Block.h"

//�����K�u���b�N�N���X
class BrickBlock : public Block
{

public:

	//�R���X�g���N�^
	BrickBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name) {}

};
