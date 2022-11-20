#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

//メインモブクラス
class MainMob : public Mob
{
public:

	//コンストラクタ
	MainMob(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name) {}

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override
	{
		//アニメーション
		Model::SetAnimFrame(hModel_, 0, 120, 1);
		Model::SetAnimFlag(hModel_,true);
	}
};
