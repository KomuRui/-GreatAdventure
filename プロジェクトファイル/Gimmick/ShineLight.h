#pragma once
#include "../Mob.h"
#include "../Engine/GameManager.h"

/// <summary>
/// 光るライトギミック
/// </summary>
class ShineLight : public Mob
{
	//変数

	int lightNum_;        //ライトの番号
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
	
	/// <summary>
	/// 光らせないようにセット
	/// </summary>
	void SetNotShineLight();

	//光らせるか光らせないかをセット

	/// <summary>
	/// 光らせるか光らせないかをセット
	/// </summary>
	/// <param name="flag">光らせるならtrue,光らせないのならfalse</param>
	void SetShineFlag(const bool& flag) { shineFlag_ = flag; }

	/// <summary>
	/// 光っているか
	/// </summary>
	/// <returns>光っているならtrue,光っていないのならfalse</returns>
	bool IsShine() { return shineFlag_; }

};

