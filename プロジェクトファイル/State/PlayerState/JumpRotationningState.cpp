#include "JumpRotationningState.h"
#include "../../Engine/Input.h"
#include "../../Engine/GameManager.h"
#include "PlayerState.h"

//定数
namespace
{
	const float JUMP_VECTOR_SIZE = 0.5f;   //ジャンプベクトルの大きさ
	const float ADD_ROTATION_ANGLE = 0.5f; //回転するとき加算する角度
	const float JUMP_VECTOR_DOWN = 0.015f; //ジャンプベクトルを小さくしていくときの値
}

//更新
void JumpRotationningState::Update2D()
{
	//符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vJamp_, vJamp_ - (UP_VECTOR * JUMP_VECTOR_DOWN));
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + ADD_ROTATION_ANGLE);

	//入力処理を呼ぶ
	HandleInput();
}

//3D用更新
void JumpRotationningState::Update3D()
{
	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() * JUMP_VECTOR_DOWN);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + ADD_ROTATION_ANGLE);

	//入力処理を呼ぶ
	HandleInput();
}

//入力によって状態変化する
void JumpRotationningState::HandleInput()
{
}

//状態変化したとき一回だけ呼ばれる関数
void JumpRotationningState::Enter()
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
		Update3D();
	else
		Update2D();
}