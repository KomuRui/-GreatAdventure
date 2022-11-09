#pragma once
#include "../Mob.h"

//アイテムブロッククラス
class ItemBlock : public Mob
{
	int status_;

public:

	//コンストラクタ
	ItemBlock(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(0){}

	//アップデート
	void UpdateMove() override
	{
		if (status_ == 1) move();
	}

	//ブロックの動き
	void move()
	{
		Angle += 0.05;
	}

	//状態セット
	void SetStatus(int num)
	{
		status_ = num;
	}
};
