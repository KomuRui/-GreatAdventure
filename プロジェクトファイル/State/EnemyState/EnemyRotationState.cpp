#include "EnemyRotationState.h"
#include "../../Engine/DirectX/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../../Enemy/Enemy.h"

//更新
void EnemyRotationState::Update2D(Enemy* enemy)
{
	//入力処理
	HandleInput(enemy);
}

//3D用更新
void EnemyRotationState::Update3D(Enemy* enemy)
{
	//回転
	enemy->Rotation();

	//入力処理
	HandleInput(enemy);
}

//入力によって状態変化する
void EnemyRotationState::HandleInput(Enemy* enemy)
{
}

//状態変化したとき一回だけ呼ばれる関数
void EnemyRotationState::Enter(Enemy* enemy)
{
	//もしボスなら
	if (enemy->GetObjectName().find("Boss") != string::npos)
	{
		//Playerのポジションゲット(Yを同じにする)
		XMFLOAT3 playerPos = GameManager::GetpPlayer()->GetPosition();
		ARGUMENT_INITIALIZE(playerPos.y, enemy->GetPosition().y);

		//自身からPlayerへのベクトル
		XMVECTOR vToPlayer = XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(new XMFLOAT3(enemy->GetPosition())));

		//ベクトルのYを同じにする(２次元のように)
		XMFLOAT3 dir = VectorToFloat3(XMVector3TransformCoord(STRAIGHT_VECTOR, enemy->GetmmRotate()));
		ARGUMENT_INITIALIZE(dir.y, VectorToFloat3(vToPlayer).y);

		//自身からPlayerへのベクトルと自身の前ベクトルとの内積を調べる
		float dotX =  GetDotRadians(XMLoadFloat3(&dir), vToPlayer);

		//どっち方向に回転させるか決めるために外積を求める
		XMVECTOR cross = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&dir), vToPlayer));

		//符号
		int sign = 1;

		//符号が違うなら
		if (signbit(XMVectorGetY(cross)) != signbit(XMVectorGetY(enemy->GetNormal())))
			sign *= -1;

		//回転する方向設定
		enemy->SetRotationSign(sign);

		//回転角度設定
		enemy->SetRotationAngle(dotX);

		//どのくらい回転したかを初期化
		enemy->SetRotationTotal(ZERO);
	}
	else
	{
		//回転する方向設定
		enemy->SetRotationSign(rand() % 2 == 1 ? 1 : -1);

		//回転角度設定
		enemy->SetRotationAngle(XMConvertToRadians((rand() % 141) + 40));

		//どのくらい回転したかを初期化
		enemy->SetRotationTotal(ZERO);
	}
}