#pragma once
#include "Block.h"

/// <summary>
/// ノーマルブロッククラス
/// </summary>
class NormalBlock : public Block
{

public:

	//コンストラクタ
	NormalBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name){}

};
