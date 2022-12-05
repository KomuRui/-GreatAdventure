#include "JumpRotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"

//更新
void JumpRotationningState::Update2D()
{
	//符号が同じなら
	if (signbit(XMVectorGetY(vJamp_)) == signbit(XMVectorGetY(keepJamp_)))
	{
		//Playerジャンプ移動
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (XMVectorSet(0,1,0,0) / 60))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (XMVectorSet(0, 1, 0, 0) / 60);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + 0.5);

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
		GameManager::GetpPlayer()->SetPosition(Transform::Float3Add(GameManager::GetpPlayer()->GetPosition(), Transform::VectorToFloat3(vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60))));

		//どんどんジャンプベクトルを小さくしていく
		vJamp_ = vJamp_ - (GameManager::GetpPlayer()->GetNormal() / 60);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + 0.5);

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
		ARGUMENT_INITIALIZE(vJamp_, GameManager::GetpPlayer()->GetNormal() / 2);
	}
	else
		ARGUMENT_INITIALIZE(vJamp_, (XMVectorSet(0, 1, 0, 0)) / 2);

	//基となるジャンプベクトルを保存しておく
	ARGUMENT_INITIALIZE(keepJamp_, vJamp_);

	//3Dと2Dで呼ぶ関数変える
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D();
	else
		Update2D();
}