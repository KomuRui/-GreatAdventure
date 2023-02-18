#include "KnockBackState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Engine/Global.h"
#include "../../Player/PlayerBase.h"
#include "PlayerStateManager.h"

//定数
namespace
{
	static const int RAY_DISTANCE = 1;                          //レイの距離
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	    //ノックバック想定距離
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;		//ノックバックの差分距離
	static const float INTERPOLATION_COEFFICIENT = 0.08f;		//補間係数
	static const float FLY_VECTOR_SIZE = 0.5f;					//FLYベクトルの大きさ
	static const float FLY_VECTOR_DOWN = 0.015f;				//FLYベクトルを小さくしていくときの値
}

//更新
void KnockBackState::Update2D(PlayerBase* player)
{

	HandleInput(player);
}

//3D用更新
void KnockBackState::Update3D(PlayerBase* player)
{

	//ノックバック(指定の場所まで補間してゆっくり行くように)
	player->SetPosition(VectorToFloat3(XMVectorLerp(XMLoadFloat3(new XMFLOAT3(player->GetPosition())), knockBackDir_, INTERPOLATION_COEFFICIENT)));

	//距離
	float dist = RangeCalculation(player->GetPosition(), VectorToFloat3(knockBackDir_));

	//壁に埋まらないようにするためにレイを飛ばす
	RayCastData data;
	data.start = player->GetPosition();     
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(player->GetPosition())) - XMLoadFloat3(new XMFLOAT3(player->GetPosition()))));
	Model::RayCast(GameManager::GetpStage()->GethModel(), &data); 

	//埋まった分戻す
	if (data.dist <= RAY_DISTANCE)
	{
		//立っている状態に
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//基となるジャンプベクトルと符号が同じなら
	if (signbit(XMVectorGetY(vFly_)) == signbit(XMVectorGetY(keepFly_)))
	{
		//ベクトルの長さ調べる
		float len = sqrtf(XMVectorGetX(vFly_) * XMVectorGetX(vFly_) + XMVectorGetY(vFly_) * XMVectorGetY(vFly_) + XMVectorGetZ(vFly_) * XMVectorGetZ(vFly_));

		//フライベクトルをキャラの上軸に直す
		ARGUMENT_INITIALIZE(vFly_, player->GetNormal() * len);

		//空飛ばせる
		player->SetPosition(Float3Add(player->GetPosition(), VectorToFloat3(vFly_ - (player->GetNormal() * FLY_VECTOR_DOWN))));

		//どんどんジャンプベクトルを小さくしていく
		ARGUMENT_INITIALIZE(vFly_, vFly_ - (player->GetNormal() * FLY_VECTOR_DOWN));
	}

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//立っている状態に
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	HandleInput(player);
}

//入力によって状態変化する
void KnockBackState::HandleInput(PlayerBase* player)
{
}

//状態変化したとき一回だけ呼ばれる関数
void KnockBackState::Enter(PlayerBase* player)
{
	//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
	knockBackDir_ = (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(player->GetPosition())) - XMLoadFloat3(&hitEnemyPos_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(new XMFLOAT3(player->GetPosition()));

	//どのくらい空飛ぶか設定
	ARGUMENT_INITIALIZE(vFly_, player->GetNormal() * FLY_VECTOR_SIZE);

	//基となるFlyベクトルを保存しておく
	ARGUMENT_INITIALIZE(keepFly_, vFly_);


	//3Dと2Dで呼ぶ関数変える
	if (GameManager::GetpStage()->GetthreeDflag())
		Update3D(player);
	else
		Update2D(player);
}