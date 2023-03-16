#include "JumpingState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../../Player/PlayerBase.h"
#include "PlayerStateManager.h"

//定数
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //ジャンプベクトルの大きさ
	const float JUMP_VECTOR_DOWN = 0.015f; //ジャンプベクトルを小さくしていくときの値
}

//更新
void JumpingState::Update2D(PlayerBase* player)
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}

	HandleInput(player);
}

//3D用更新
void JumpingState::Update3D(PlayerBase* player)
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//ベクトルの長さ調べる
		float len = sqrtf(XMVectorGetX(vJamp_) * XMVectorGetX(vJamp_) + XMVectorGetY(vJamp_) * XMVectorGetY(vJamp_) + XMVectorGetZ(vJamp_) * XMVectorGetZ(vJamp_));

		//ジャンプベクトルをキャラの上軸に直す
		ARGUMENT_INITIALIZE(vJamp_,player->GetNormal() * len);

		//Playerジャンプ移動
		player->SetPosition(Float3Add(player->GetPosition(),VectorToFloat3(vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_,vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN));
	}

	HandleInput(player);
}

//入力によって状態変化する
void JumpingState::HandleInput(PlayerBase* player)
{
	//ジャンプ回転状態に変更
	if (Input::GetPadTrrigerR() && GameManager::GetpSceneManager()->GetSceneId() != SCENE_ID_MINIGAME)
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumpRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//状態変化したとき一回だけ呼ばれる関数
void JumpingState::Enter(PlayerBase* player)
{
	//ジャンプのベクトル・フラグ初期化
	//3Dと2Dで初期化の値変える
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, player->GetNormal() * JUMP_VECTOR_SIZE);
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