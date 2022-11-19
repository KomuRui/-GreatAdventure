#pragma once
#include "Block.h"

//ノーマルブロッククラス
class NormalBlock : public Block
{

public:

	//コンストラクタ
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

};
