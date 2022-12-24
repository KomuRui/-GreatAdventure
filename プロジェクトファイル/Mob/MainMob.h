#pragma once
#include "../Mob.h"
#include "../Engine/Model.h"

/// <summary>
/// メインモブキャラ
/// </summary>
class MainMob : public Mob
{
public:

	//コンストラクタ
	MainMob(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name) {}

	//更新の前に一度だけ呼ばれる
	void ChildStartUpdate() override;
};
