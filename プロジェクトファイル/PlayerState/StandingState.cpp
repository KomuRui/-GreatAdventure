#include "StandingState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "../Engine/Model.h"
#include "PlayerState.h"

//更新
void StandingState::Update2D()
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

	//入力処理関数を呼ぶ
	HandleInput();
}

//3D用更新
void StandingState::Update3D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::BlockRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//当たった距離が0.9fより小さいなら
	if (dataNormal.dist < 0.9f)
	{
		//地形に高さ合わせる
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//入力処理関数を呼ぶ
	HandleInput();
}

//入力によって状態変化する
void StandingState::HandleInput()
{
	//ジャンプ状態に変更
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerState::state_ = PlayerState::jumping_;
		PlayerState::state_->Enter();
	}

	//回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerState::state_ = PlayerState::rotationning_;
		PlayerState::state_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter()
{
}
