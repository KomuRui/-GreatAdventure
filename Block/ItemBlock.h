#pragma once
#include "Block.h"

//アイテムブロッククラス
class ItemBlock : public Block
{
	int status_;

public:

	//コンストラクタ
	ItemBlock(GameObject* parent, std::string modelPath, std::string name) :Block(parent, modelPath, name), status_(0){}

	//アップデート
	void BlockChildUpdate() override
	{
		if (status_ == 1) move();
	}

	//ブロックの動き
	void move()
	{
		Angle += 0.05;
	}

	//状態セット
	void SetStatus(const int& num)
	{
		status_ = num;
	}
};
