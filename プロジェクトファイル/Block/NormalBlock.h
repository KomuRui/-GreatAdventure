#pragma once
#include "Block.h"

//�m�[�}���u���b�N�N���X
class NormalBlock : public Block
{

public:

	//�R���X�g���N�^
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

};
