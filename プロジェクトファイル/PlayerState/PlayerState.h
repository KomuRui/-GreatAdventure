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
	static State* playerState_;

	//各状態変数
	static JumpingState*          playerJumping_;             //ジャンプ
	static JumpRotationningState* playerJumpRotationning_;    //ジャンプ回転
	static RotationningState*     playerRotationning_;		  //回転
	static RunningState*          playerRunning_;		      //走る
	static StandingState*		  playerStanding_;			  //立ってる
	static WalkingState* 		  playerWalking_;			  //歩く

    //コンストラクタ
	PlayerState();

	//2D用更新
	void Update2D() override;

	//3D用更新
	void Update3D() override;

	//入力によって状態変化する
	void HandleInput() override;

	//状態変化したとき一回だけ呼ばれる関数
	void Enter() override;

};



