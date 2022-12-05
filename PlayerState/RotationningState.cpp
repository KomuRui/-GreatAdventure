#include "RotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"
#include "../Engine/Model.h"

//更新
void RotationningState::Update2D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	XMFLOAT3 moveY2 = { 0,-1,0 };
	dataNormal.dir = moveY2;
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//当たった距離が1.0fより小さいなら
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (1 - (rotationCount_ * 0.015f)));

	//もし回転を始めてから60フレーム以上が経過しているなら
	if (rotationCount_ >= 60)
	{
	    //回転停止
	    rotationCount_ = 0;

		//状態変更
		PlayerState::state_ = PlayerState::standing_;
	}

	//rotationCount1ずつ増やす
	rotationCount_++;

	HandleInput();
}

//入力によって状態変化する
void RotationningState::HandleInput()
{
	//ジャンプ状態に変更
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerState::state_ = PlayerState::jumping_;
		PlayerState::state_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void RotationningState::Enter()
{
	//0に初期化
	ZERO_INITIALIZE(rotationCount_);
}