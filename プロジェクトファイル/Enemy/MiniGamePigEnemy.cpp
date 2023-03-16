#include "MiniGamePigEnemy.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/MiniGameManager/MiniGameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/GameObject/Camera.h"

//定数
namespace
{

	//////////////////////キャラの必要な情報//////////////////////

	static const int RAY_DISTANCE = 1;                        //レイの距離
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	  //ノックバック想定距離
	static const float KNOCKBACK_DIFFERENCIAL_DISTANCE = 5.0f;//ノックバックの差分距離
	static const float INTERPOLATION_COEFFICIENT = 0.08f;     //補間係数
	static const float HIT_STOP_TIME = 0.15f;                 //ヒットストップ演出の時間
	static const float FLY_VECTOR_SIZE = 1.0f;				  //FLYベクトルの大きさ
	static const float FLY_VECTOR_DOWN = 0.015f;			  //FLYベクトルを小さくしていくときの値
	static const float DIE_TIME = 1.0f;                       //死ぬまでの時間

	//////////////////////カメラ//////////////////////

	static const float VIBRATION_INTENSITY = 0.4f; //振動の強さ
}

//コンストラクタ
MiniGamePigEnemy::MiniGamePigEnemy(GameObject* parent)
	:PigEnemy(parent,"MiniGamePigEnemy")
{}

//更新の前に一度だけ呼ばれる関数
void MiniGamePigEnemy::ChildPigEnemyStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);


	///////////////角度反転///////////////////

	angle_ += XMConvertToRadians(180);
}

//更新
void MiniGamePigEnemy::ChildPigEnemyUpdate()
{
	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z - 5)
		KillMe();

	//ノックバックしてなく死んでいないのなら
	if (pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
}

//ノックバックして死亡
void MiniGamePigEnemy::KnockBackDie()
{
	//ノックバックしていないのなら
	if (!isKnockBack_)
	{
		//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
		knockBackDir_ = (XMVectorSet(0, 0, 10, 0) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//どのくらい空飛ぶか設定
		ARGUMENT_INITIALIZE(vFly_, GameManager::GetpPlayer()->GetNormal() * FLY_VECTOR_SIZE);

		//基となるFlyベクトルを保存しておく
		ARGUMENT_INITIALIZE(keepFly_, vFly_);

		//ノックバックした
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);
	}

	//ノックバック(指定の場所まで補間してゆっくり行くように)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, INTERPOLATION_COEFFICIENT));

	//距離
	float dist = RangeCalculation(transform_.position_, VectorToFloat3(knockBackDir_));

	//壁に埋まらないようにするためにノックバック方向にレイを飛ばす
	RayCastData data;
	data.start = transform_.position_;
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::RayCast(hGroundModel_, &data);

	//埋まった分戻す
	if (data.dist <= RAY_DISTANCE)
	{
		//死亡状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}

	//ノックバックしているなら
	if (isKnockBack_)
	{
		//基となるジャンプベクトルと符号が同じなら
		if (signbit(XMVectorGetY(vFly_)) == signbit(XMVectorGetY(keepFly_)))
		{
			//ベクトルの長さ調べる
			float len = sqrtf(XMVectorGetX(vFly_) * XMVectorGetX(vFly_) + XMVectorGetY(vFly_) * XMVectorGetY(vFly_) + XMVectorGetZ(vFly_) * XMVectorGetZ(vFly_));

			//フライベクトルをキャラの上軸に直す
			ARGUMENT_INITIALIZE(vFly_, vNormal_ * len);

			//空飛ばせる
			ARGUMENT_INITIALIZE(transform_.position_, Float3Add(transform_.position_, VectorToFloat3(vFly_ - (vNormal_ * FLY_VECTOR_DOWN))));

			//どんどんジャンプベクトルを小さくしていく
			ARGUMENT_INITIALIZE(vFly_, vFly_ - (vNormal_ * FLY_VECTOR_DOWN));
		}

		Model::SetAnimFrame(hModel_, 80, 80, ZERO);
	}

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//ノックバックしてない状態に
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//死亡状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}
}

//死亡
void MiniGamePigEnemy::Die()
{
	//待機状態に変更
	ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

	//吹っ飛ばされるアニメーションに
	Model::SetAnimFrame(hModel_, 80, 80, ZERO);

	//死ぬエフェクト
	EnemyEffectManager::DieEffect(transform_.position_, up_);

	//コライダーを削除
	KillCollider(collision);

	//削除
	KillMe();
}

//何かのオブジェクトに当たった時に呼ばれる関数
void MiniGamePigEnemy::OnCollision(GameObject* pTarget)
{
	//もしPlayerと当たったら
	if (pTarget->GetObjectName() == "Player")
	{
		
		//もしPlayerが回転していたらかつ自身が死んでいないなら
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			MiniGameManager::SetRunSpeed(8.0f);
			MiniGameManager::SetRunMode(true);
			MiniGameManager::AddCombo();
			MiniGameManager::SetComboTextScale(1.3f);

			//当たった位置を調べる
			XMFLOAT3 hitPos = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//エフェクト表示
			EnemyEffectManager::HitEffect(hitPos, transform_.position_);

			//カメラ振動
			Camera::SetCameraVibration(VIBRATION_INTENSITY, 0.02f);

			//ノックバックして死亡させる
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//終了
			return;

		}
	}
}