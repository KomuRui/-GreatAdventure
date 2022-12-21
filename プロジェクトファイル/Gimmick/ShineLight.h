#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

class ShineLight : public Mob
{

	//定数

	const int LIGHT_INTENSITY = 2;	 //ライトの強さ
	const int REACTION_DISTANCE = 4; //反応距離

	//変数

	int lightNum_;        //ライトの番号
	float  num_;          //数
	bool shineFlag_;      //光っているかどうか
	bool shinePermitFlag_;//光るのを許可するかどうか

public:

	/////////////////////オーバーライドする関数//////////////////////

	//スタートアップデート
	void ChildStartUpdate() override;

	//ワープの動き方
	void ChildUpdate() override;

	//指定した時間で呼ばれるメソッド
	void TimeMethod() override;

	////////////////////関数//////////////////////
 
	//コンストラクタ
	ShineLight(GameObject* parent, std::string modelPath, std::string name);

	////////////////////セッターゲッター//////////////////////
	
	//光らないようにセット
	void SetNotShineLight();

	//光らせるか光らせないかをセット
	void SetShineFlag(const bool& flag) { shineFlag_ = flag; }

	//光っているかどうかゲットする
	bool GetShineFlag() { return shineFlag_; }

};

