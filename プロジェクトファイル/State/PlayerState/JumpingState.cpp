#include "JumpingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Global.h"
#include "PlayerStateManager.h"

//定数
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //ジャンプベクトルの大きさ
	const float JUMP_VECTOR_DOWN = 0.015f; //ジャンプベクトルを小さくしていくときの値
}

//更新
void JumpingState::Update2D(Player* player)
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}

	HandleInput(player);
}

//3D用更新
void JumpingState::Update3D(Player* player)
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//ベクトルの長さ調べる
		float len = sqrtf(XMVectorGetX(vJamp_) * XMVectorGetX(vJamp_) + XMVectorGetY(vJamp_) * XMVectorGetY(vJamp_) + XMVectorGetZ(vJamp_) * XMVectorGetZ(vJamp_));

		//ジャンプベクトルをキャラの上軸に直す
		vJamp_ = GameManager::GetpPlayer()->GetNormal() * len;

		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(),VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_,vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN));
	}

	HandleInput(player);
}

//入力によって状態変化する
void JumpingState::HandleInput(Player* player)
{
	//ジャンプ回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumpRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//状態変化したとき一回だけ呼ばれる関数
void JumpingState::Enter(Player* player)
{
	//ジャンプのベクトル・フラグ初期化
	//3Dと2Dで初期化の値変える
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_SIZE);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR * JUMP_VECTOR_SIZE);
	
	//基となるジャンプベクトルを保存しておく
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3Dと2Dで呼ぶ関数変える
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}