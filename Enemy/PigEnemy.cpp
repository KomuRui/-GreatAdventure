#include "PigEnemy.h"
#include "../Engine/Model.h"

//コンストラクタ
PigEnemy::PigEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), knockBackFlag_(false)
{
}

//更新の前に一回呼ばれる関数
void PigEnemy::EnemyChildStartUpdate()
{

	///////////////当たり判定設定///////////////////

	//玉
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0), 1.7f);
	AddCollider(collision);

	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, 1, 60, 2);
}

//更新
void PigEnemy::EnemyChildUpdate()
{
	//コライダーのポジション変更
	SetPosCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0));
}

//ノックバックして死亡
void PigEnemy::KnockBackDie()
{
	//ノックバックしていないのなら
	if (!knockBackFlag_)
	{
		//Playerのポジションゲット
		XMFLOAT3 playerPos = pPlayer_->GetPosition();

		//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_)) * 10) + XMLoadFloat3(&transform_.position_);

		//ノックバックした
		knockBackFlag_ = !knockBackFlag_;
	}

	//ノックバック(指定の場所まで補間してゆっくり行くように)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, 0.08));

	//どこまでノックバックしたかいれる変数
	XMFLOAT3 knockBackPos;
	XMStoreFloat3(&knockBackPos, knockBackDir_);

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (Transform::RangeCalculation(transform_.position_, knockBackPos) < 1)
	{
		knockBackFlag_ = !knockBackFlag_;
		aiState_ = WAIT;
	}
}

//死亡
void PigEnemy::Die()
{
}

//何かのオブジェクトに当たった時に呼ばれる関数
void PigEnemy::TimeMethod()
{
	Enter();
}

//何かのオブジェクトに当たった時に呼ばれる関数
void PigEnemy::OnCollision(GameObject* pTarget)
{
	//もしPlayerと当たったら
	if (pTarget->GetObjectName() == "Player")
	{
		//もしPlayerが回転していたら
		if (pPlayer_->GetRotationFlag())
		{
			//ヒットストップ演出(すこしゆっくりに)
			Leave();
			pTarget->Leave();

			//Playerも敵も1.0秒後に動き出す
			SetTimeMethod(0.1f);
			pTarget->SetTimeMethod(0.1f);

			//ノックバックして死亡させる
			aiState_ = KNOCKBACK_DIE;

		}
	}
}
