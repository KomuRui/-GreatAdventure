#include "StandingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "PlayerStateManager.h"
#include "../../Player/PlayerBase.h"

//更新
void StandingState::Update2D(PlayerBase* player)
{
	//レイを下に飛ばす
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(DOWN_VECTOR));
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//レイの当たった距離が1.0fより小さいなら
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		player->SetPosition(dataNormal.pos);
		player->SetAcceleration(1);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void StandingState::Update3D(PlayerBase* player)
{
	//レイを下に飛ばす
	RayCastData dataNormal;
	ARGUMENT_INITIALIZE(dataNormal.start,player->GetPosition());
	ARGUMENT_INITIALIZE(dataNormal.dir,VectorToFloat3(player->GetDown()));
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//当たった距離が0.9fより小さいなら
	if (dataNormal.dist < 0.9f)
	{
		//地形に高さ合わせる
		player->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + player->GetNormal()));
		player->SetAcceleration(1);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void StandingState::HandleInput(PlayerBase* player)
{
	//ジャンプ状態に変更
	if(Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}

	//回転状態に変更
	if (Input::GetPadTrrigerR())
	{
		//状態変更
		PlayerStateManager::playerState_ = PlayerStateManager::playerRotationning_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//状態変化したとき一回だけ呼ばれる関数
void StandingState::Enter(PlayerBase* player)
{
}
