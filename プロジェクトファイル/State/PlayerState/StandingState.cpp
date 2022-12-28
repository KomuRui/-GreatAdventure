#include "StandingState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Model.h"
#include "../../Engine/ImGuiSet.h"
#include "PlayerStateManager.h"

//更新
void StandingState::Update2D(Player* player)
{
	//レイを下に飛ばす
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(DOWN_VECTOR);
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//レイの当たった距離が1.0fより小さいなら
	if (dataNormal.dist < 1.0f)
	{
		dataNormal.pos.y += 1.0f;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//3D用更新
void StandingState::Update3D(Player* player)
{
	//レイを下に飛ばす
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//当たった距離が0.9fより小さいなら
	if (dataNormal.dist < 0.9f)
	{
		//地形に高さ合わせる
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//入力処理関数を呼ぶ
	HandleInput(player);
}

//入力によって状態変化する
void StandingState::HandleInput(Player* player)
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
void StandingState::Enter(Player* player)
{
}
