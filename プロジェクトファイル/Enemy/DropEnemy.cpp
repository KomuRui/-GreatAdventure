#include "DropEnemy.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//定数
namespace
{
	//////////////////////アニメーション//////////////////////

	static const int ANIM_START_FRAME = 1; //開始フレーム
	static const int ANIM_END_FRAME = 60;  //終了フレーム
	static const int ANIM_DIE_FRAME = 70;  //死亡フレーム
	static const float ANIM_SPEED = 3.0f;  //アニメスピード

	//////////////////////キャラの必要な情報//////////////////////

	static const int RAY_DISTANCE = 1;                                 //レイの距離
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 10;	           //ノックバック想定距離
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;			   //ノックバックの差分距離
	static const float INTERPOLATION_COEFFICIENT = 0.08f;			   //補間係数
	static const float HIT_STOP_TIME = 0.15f;						   //ヒットストップ演出の時間
	static const XMFLOAT4 HED_NORMAL_COLOR = { ZERO,ZERO,1.0f,1.0f };  //ノーマル状態の頭の色
	static const XMFLOAT4 HED_FOUND_COLOR = { 1.0f,ZERO,ZERO,1.0f };   //見つけた時の頭の色

	//////////////////////カメラ//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //振動の強さ
}

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
	assert(hHedModel_ >= ZERO);

	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, HED_NORMAL_COLOR);

	///////////////当たり判定設定///////////////////

	//玉
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)), ZERO), 1.7f);
	AddCollider(collision);

	///////////////エフェクト///////////////////

	//エフェクト出すために必要なクラス
	pParticle_ = Instantiate<Particle>(this);
	 
	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

}

//更新
void DropEnemy::EnemyChildUpdate()
{
	//コライダーのポジション変更
	SetPosCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)), ZERO));
}

//描画
void DropEnemy::EnemyChildDraw()
{
	Model::SetTransform(hHedModel_, transform_);
	Model::Draw(hHedModel_);
}

//当たった時のエフェクト
void DropEnemy::HitEffect(const XMFLOAT3& pos)
{
	EmitterData data;
	data.textureFileName = "Cloud.png";
	data.position = pos;
	data.delay = 0;
	data.number = 30;
	data.lifeTime = 20;
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.1f;
	data.speedErr = 0.8;
	data.size = XMFLOAT2(1, 1);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	pParticle_->Start(data);
}

//Playerが視角内、指定距離内にいる時の処理
void DropEnemy::PlayerWithIf()
{
	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, HED_NORMAL_COLOR);
}

//Playerが視角内、指定距離内にいない時の処理
void DropEnemy::NotPlayerWithIf()
{
	//頭の部分の色を変更
	Model::SetSpeculer(hHedModel_, HED_FOUND_COLOR);
}

//ノックバックして死亡
void DropEnemy::KnockBackDie()
{
	//ノックバックしていないのなら
	if (!knockBackFlag_)
	{
		//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//ノックバックした
		ARGUMENT_INITIALIZE(knockBackFlag_, !knockBackFlag_);
	}

	//ノックバック(指定の場所まで補間してゆっくり行くように)
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), knockBackDir_, INTERPOLATION_COEFFICIENT));

	//距離
	float dist = RangeCalculation(transform_.position_, VectorToFloat3(knockBackDir_));

	//壁に埋まらないようにするためにレイを飛ばす
	RayCastData data;
	data.start = transform_.position_;     //レイの発射位置
	XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)));
	Model::RayCast(hGroundModel_, &data);  //レイを発射

	//埋まった分戻す
	if (data.dist <= RAY_DISTANCE)
	{
		XMVECTOR dis = -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * data.dist;
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) - dis));

		//戻したら距離を0に初期化
		ZERO_INITIALIZE(dist);
	}

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//ノックバックしていない状態にする
		ARGUMENT_INITIALIZE(knockBackFlag_, !knockBackFlag_);

		//待機状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyWaitState());
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
		//もしPlayerが回転していたらかつ自身が死んでいないなら
		if (GameManager::GetpPlayer()->IsRotation() && pState_ != EnemyStateList::GetEnemyKnockBackState() && pState_ != EnemyStateList::GetEnemyDieState())
		{
			//ヒットストップ演出(すこしゆっくりに)
			Leave();
			pTarget->Leave();

			//Playerも敵も0.15秒後に動き出す
			SetTimeMethod(HIT_STOP_TIME);
			pTarget->SetTimeMethod(HIT_STOP_TIME);

			//当たったポジションを保存する変数
			XMFLOAT3 hitPos;

			//当たった位置を調べる
			XMStoreFloat3(&hitPos,XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

			//エフェクト表示
			HitEffect(hitPos);

			//カメラ振動
			Camera::SetCameraVibration(VIBRATION_INTENSITY);

			//ノックバックして死亡させる
			ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

			//終了
			return;
		}
	}
}
