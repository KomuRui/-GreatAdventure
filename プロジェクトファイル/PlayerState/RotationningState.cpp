#include "RotationningState.h"
#include "../Engine/Input.h"
#include "../Engine/GameManager.h"
#include "PlayerState.h"
#include "../Engine/Model.h"

//定数
namespace
{
	static const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");	//FPS
	static const int NORMAL_ROTATION_ANGLE = 1;       //回転するときの加算する角度
	static const float ROTATION_ATTENUATION = 0.015f; //回転の減衰
	static const float HIT_DISTANCE_2D = 1.0f; //レイの当たった距離(2D)
	static const float HIT_DISTANCE    = 0.9f; //レイの当たった距離(3D)
}

//更新
void RotationningState::Update2D()
{
	//下にレイを飛ばす
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(DOWN_VECTOR);
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//レイの当たった距離が1.0fより小さいなら
	if (dataNormal.dist < HIT_DISTANCE_2D)
	{
		dataNormal.pos.y += HIT_DISTANCE_2D;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//もし回転を始めてから60フレーム以上が経過しているなら
	if (rotationCount_ >= FPS)
	{
	    //回転停止
		ARGUMENT_INITIALIZE(rotationCount_,ZERO);

		//状態変更
		PlayerState::playerState_ = PlayerState::playerStanding_;
	}

	//rotationCount1ずつ増やす
	rotationCount_++;

	HandleInput();
}

//3D用更新
void RotationningState::Update3D()
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//当たった距離が0.9fより小さいなら
	if (dataNormal.dist < HIT_DISTANCE)
	{
		//地形に高さ合わせる
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//エフェクトの表示
	GameManager::GetpPlayer()->RotationEffect();

	//Playerの上軸少し回転させる
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//もし回転を始めてから60フレーム以上が経過しているなら
	if (rotationCount_ >= FPS)
	{
		//回転停止
		ARGUMENT_INITIALIZE(rotationCount_, ZERO);

		//状態変更
		PlayerState::playerState_ = PlayerState::playerStanding_;
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
		PlayerState::playerState_ = PlayerState::playerJumping_;
		PlayerState::playerState_->Enter();
	}
}

//状態変化したとき一回だけ呼ばれる関数
void RotationningState::Enter()
{
	//0に初期化
	ZERO_INITIALIZE(rotationCount_);
}