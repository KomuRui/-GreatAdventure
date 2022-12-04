#include "PlayerState.h"

//各static変数の初期化
JumpingState* PlayerState::jumping_ = new JumpingState;
JumpRotationningState* PlayerState::jumpRotationning_ = new JumpRotationningState;
RotationningState* PlayerState::rotationning_ = new RotationningState;
RunningState* PlayerState::running_ = new RunningState;
StandingState* PlayerState::standing_ = new StandingState;
WalkingState* PlayerState::walking_ = new WalkingState;


//コンストラクタ
PlayerState::PlayerState()
{
	//最初の状態は立ってるにしておく
	ARGUMENT_INITIALIZE(state_, standing_);
}

//更新
void PlayerState::Update()
{
	//現在の状態の更新を呼ぶ
	state_->Update();
}

//入力によって状態変化する
void PlayerState::HandleInput()
{
	//現在の状態の入力処理を呼ぶ
	state_->HandleInput();
}

//状態変化したとき一回だけ呼ばれる関数
void PlayerState::Enter()
{
	//現在の状態のEnter関数を呼ぶ
	state_->Enter();
}
