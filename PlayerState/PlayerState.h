#pragma once
#include "../Engine/Input.h"
#include "State.h"
#include "JumpingState.h"
#include "JumpRotationningState.h"
#include "RotationningState.h"
#include "RunningState.h"
#include "StandingState.h"
#include "WalkingState.h"
#include "../Engine/Global.h"

//Playerの状態の基底クラス
class PlayerState : public State
{
private:

	//キャラの前方向のベクトル
	XMVECTOR front_;                        

public:

	//状態を示す変数
	static State* state_;

	//各状態変数
	static JumpingState*          jumping_;             //ジャンプ
	static JumpRotationningState* jumpRotationning_;    //ジャンプ回転
	static RotationningState*     rotationning_;		//回転
	static RunningState*          running_;				//走る
	static StandingState*		  standing_;			//立ってる
	static WalkingState* 		  walking_;				//歩く

    //コンストラクタ
	PlayerState();

	//更新
	void Update2D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;
};



