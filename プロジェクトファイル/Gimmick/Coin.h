#pragma once
#include "../Mob.h"

/// <summary>
/// コインクラス
/// </summary>
class Coin : public Mob
{
public:

	//コンストラクタ
	Coin(GameObject* parent, std::string modelPath,std::string name) :Mob(parent, modelPath,name){}

	//更新の前に一度だけ呼ばれる関数
	void ChildStartUpdate() override;

	//更新
	void ChildUpdate() override;

	//当たり判定
	void OnCollision(GameObject* pTarget) override;
};
