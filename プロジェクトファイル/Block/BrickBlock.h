#pragma once
#include "Block.h"

//レンガブロッククラス
class BrickBlock : public Block
{

public:

	//コンストラクタ
	BrickBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name) {}

};
