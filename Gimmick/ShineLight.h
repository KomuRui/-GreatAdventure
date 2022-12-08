#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

class ShineLight : public Mob
{

	//定数

	const int LIGHT_INTENSITY = 2;	 //ライトの強さ
	const int REACTION_DISTANCE = 3; //反応距離

	//変数

	int lightNum_;    //ライトの番号
	float  num_;      //数
	bool shineFlag_;  //光っているかどうか

public:

	//コンストラクタ
	ShineLight(GameObject* parent, std::string modelPath, std::string name);

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;
};

