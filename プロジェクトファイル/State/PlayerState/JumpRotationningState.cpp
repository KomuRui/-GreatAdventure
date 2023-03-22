#include "JumpRotationningState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "PlayerStateManager.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"
#include "../../Player/PlayerBase.h"
#include "../../Manager/AudioManager/PlayerAudioManager/PlayerAudioManager.h"

//定数
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //ジャンプベクトルの大きさ
	const float ADD_ROTATION_ANGLE = 0.5f; //回転するとき加算する角度
	const float JUMP_VECTOR_DOWN = 0.015f; //ジャンプベクトルを小さくしていくときの値
}

//更新
void JumpRotationningState::Update2D(PlayerBase* player)
{
	//符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}
	
	//エフェクトの表示
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Playerの上軸少し回転させる
	player->SetAngle(player->GetAngle() + ADD_ROTATION_ANGLE);

	//入力処理を呼ぶ
	HandleInput(player);
}

//3D用更新
void JumpRotationningState::Update3D(PlayerBase* player)
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_,vJamp_ - (player->GetNormal() * JUMP_VECTOR_DOWN));
	}

	//エフェクトの表示
	PlayerEffectManager::RotationEffect(player->GethModel());

	//Playerの上軸少し回転させる
	player->SetAngle(player->GetAngle() + ADD_ROTATION_ANGLE);

	//入力処理を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void JumpRotationningState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void JumpRotationningState::Enter(PlayerBase* player)
{
	//ジャンプのベクトル・フラグ初期化
	//3Dと2Dで初期化の値変える
	if (GameManager::GetpStage()->GetthreeDflag())
	{
		ARGUMENT_INITIALIZE(vJamp_, player->GetNormal() * JUMP_VECTOR_SIZE);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, UP_VECTOR * JUMP_VECTOR_SIZE);

	//回転音
	PlayerAudioManager::RotationAudio();

	//基となるジャンプベクトルを保存しておく
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3Dと2Dで呼ぶ関数変える
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}