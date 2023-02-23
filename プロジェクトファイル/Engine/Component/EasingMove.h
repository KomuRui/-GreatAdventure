#pragma once
#include "../ResourceManager/Global.h"

/// <summary>
/// イージングを利用して様々な移動をするクラス
/// </summary>
class EasingMove
{
	int timerhNum_;             //タイマーのハンドル番号

	float moveTime_;            //移動時間
	float nowTime_;             //現在の時間
						    
	XMFLOAT3* targetPos_;       //移動させる対象のポインタ
	XMFLOAT3 beforePos_;        //移動前のポジション
	XMFLOAT3 afterPos_;         //移動後のポジション

	float (*easingFunc)(float); //使うイージングの関数

public:

	//コンストラクタ
	EasingMove();

	//コンストラクタ
	EasingMove(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float));

	/// <summary>
	/// イージングしながら移動
	/// </summary>
	/// <returns>移動が終わっていたらtrue,終わっていなかったらfalse</returns>
	bool Move();

	/// <summary>
	/// リセットする
	/// </summary>
	/// <param name="targetPos">移動させる対象のポインタ</param>
	/// <param name="beforePos">移動前のポジション</param>
	/// <param name="afterPos">移動後のポジション</param>
	/// <param name="moveTime">移動にかかる時間</param>
	/// <param name="Func">使うイージング関数</param>
	void Reset(XMFLOAT3* targetPos, XMFLOAT3 beforePos, XMFLOAT3 afterPos, float moveTime, float (*func)(float));
};

