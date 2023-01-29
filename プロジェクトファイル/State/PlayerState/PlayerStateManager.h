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
#include "DieState.h"

//定義
class PlayerBase;

/// <summary>
/// Playerの状態を管理しているクラス
/// </summary>
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
	static DieState*              playerDieing_;              //死亡

    //コンストラクタ
	PlayerStateManager();

	//2D用更新
	virtual void Update2D(PlayerBase* player)override;

	//3D用更新
	virtual void Update3D(PlayerBase* player)override;

	//ミニゲーム用更新
	virtual void UpdateMiniGame(PlayerBase* player)override;

	//入力によって状態変化する
	virtual void HandleInput(PlayerBase* player)override;

	//状態変化したとき一回だけ呼ばれる関数
	virtual void Enter(PlayerBase* player)override;

	//状態チェンジ用
	void ChangeState(PlayerState* change, PlayerBase* player);

};



