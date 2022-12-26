#pragma once
#include "../../Engine/Input.h"
#include "PlayerState.h"
#include "../../Engine/Global.h"
#include "JumpingState.h"
#include "JumpRotationningState.h"
#include "RotationningState.h"
#include "RunningState.h"
#include "StandingState.h"
#include "WalkingState.h"

//定義
class Player;

//Playerの状態の基底クラス
class PlayerStateManager : public PlayerState
{
private:

	//キャラの前方向のベクトル
	XMVECTOR front_;                        

public:

	//状態を示す変数
	static PlayerState* playerState_;

	//各状態変数
	static JumpingState*          playerJumping_;             //ジャンプ
	static JumpRotationningState* playerJumpRotationning_;    //ジャンプ回転
	static RotationningState*     playerRotationning_;		  //回転
	static RunningState*          playerRunning_;		      //走る
	static StandingState*		  playerStanding_;			  //立ってる
	static WalkingState* 		  playerWalking_;			  //歩く

    //コンストラクタ
	PlayerStateManager();

	//2D用更新
	virtual void Update2D(Player* player);

	//3D用更新
	virtual void Update3D(Player* player);

	//入力によって状態変化する
	virtual void HandleInput(Player* player);

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter(Player* player);

};



