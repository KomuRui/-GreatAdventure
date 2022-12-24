#include "JumpingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Global.h"
#include "PlayerState.h"

//更新
void JumpingState::Update2D()
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR / 60))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (UP_VECTOR / 60);
	}

	HandleInput();
}

//3D用更新
void JumpingState::Update3D()
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//ベクトルの長さ調べる
		float len = sqrtf(XMVectorGetX(vJamp_) * XMVectorGetX(vJamp_) + XMVectorGetY(vJamp_) * XMVectorGetY(vJamp_) + XMVectorGetZ(vJamp_) * XMVectorGetZ(vJamp_));

		//ジャンプベクトルをキャラの上軸に直す
		vJamp_ = GameManager::GetpPlayer()->GetNormal() * len;

		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60);
	}

	HandleInput();
}

//入力によって状態変化する
void JumpingState::HandleInput()
{
	//ジャンプ回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerState::state_ = PlayerState::jumpRotationning_;
		PlayerState::state_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void JumpingState::Enter()
{
	//ジャンプのベクトル・フラグ初期化
	//3Dと2Dで初期化の値変える
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() / 2);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR / 2);
	
	//基となるジャンプベクトルを保存しておく
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3Dと2Dで呼ぶ関数変える
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D();
	else
		Update2D();
}