#include "DropEnemy.h"
#include "../Engine/Model.h"

//コンストラクタ
DropEnemy::DropEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), knockBackFlag_(false)
{
}

//更新の前に一回呼ばれる関数
void DropEnemy::EnemyChildStartUpdate()
{
	///////////////モデルデータのロード///////////////////

	//頭
	hHedModel_ = Model::Load("Enemy/Model/DropEnemyHed.fbx");
	assert(hHedModel_ >= 0);

	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, XMFLOAT4(0,0,1,1));

	///////////////当たり判定設定///////////////////

	//玉
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0), 1.7f);
	AddCollider(collision);

	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, 1, 60, 3);

}

//更新
void DropEnemy::EnemyChildUpdate()
{
	//コライダーのポジション変更
	SetPosCollider(XMFLOAT3(0, XMVectorGetY(XMVector3Normalize(vNormal)) * 1, 0));
}

//描画
void DropEnemy::EnemyChildDraw()
{
	Model::SetTransform(hHedModel_, transform_);
	Model::Draw(hHedModel_);
}

//Playerが視角内、指定距離内にいる時の処理
void DropEnemy::PlayerWithIf()
{
	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, XMFLOAT4(1, 0, 0, 1));
}

//Playerが視角内、指定距離内にいない時の処理
void DropEnemy::NotPlayerWithIf()
{
	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, XMFLOAT4(0, 0, 1, 1));
}

//ノックバックして死亡
void DropEnemy::KnockBackDie()
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
void DropEnemy::Die()
{
}

//何かのオブジェクトに当たった時に呼ばれる関数
void DropEnemy::TimeMethod()
{
	Enter();
}

//何かのオブジェクトに当たった時に呼ばれる関数
void DropEnemy::OnCollision(GameObject* pTarget)
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

			//Playerも敵も0.15秒後に動き出す
			SetTimeMethod(0.15f);
			pTarget->SetTimeMethod(0.15f);

			//ノックバックして死亡させる
			aiState_ = KNOCKBACK_DIE;

		}
	}
}
