#include "BossEnemy.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Gimmick/FlyBall.h"
#include "../Engine/ResourceManager/Time.h"
#include "BossEnemyChild.h"

//定数
namespace
{
	//////////////////////アニメーション//////////////////////

	static const int ANIM_START_FRAME = 1; //開始フレーム
	static const int ANIM_END_FRAME = 60;  //終了フレーム
	static const int ANIM_DIE_FRAME = 70;  //死亡フレーム
	static const float ANIM_SPEED = 3.0f;  //アニメスピード

	//////////////////////キャラの必要な情報//////////////////////

	static const int MAX_HP = 10;                               //最大体力
	static const int RAY_DISTANCE = 1;                          //レイの距離
	static const int KNOCKBACK_ASSUMPTION_DISTANCE = 7;	        //ノックバック想定距離
	static const int KNOCKBACK_DIFFERENCIAL_DISTANCE = 1;		//ノックバックの差分距離
	static const float INTERPOLATION_COEFFICIENT = 0.08f;		//補間係数
	static const float ADD_ROTATION_ANGLE = 0.02f;				//回転するときの加算する角度
	static const float HIT_STOP_TIME = 0.15f;					//ヒットストップ演出の時間
	static const float COLLIDER_SIZE = 8.0f;                    //コライダーサイズ
	static const float DIE_TIME = 2.0f;                         //死ぬまでの時間
	static const float MOVE_RAY_HIT_DISTANCE = 0.9f;			//動いているときのレイの当たった距離


	//////////////////////カメラ//////////////////////

	static const float VIBRATION_INTENSITY = 0.2f; //振動の強さ
}

//コンストラクタ
BossEnemy::BossEnemy(GameObject* parent, std::string modelPath, std::string name)
	:Enemy(parent, modelPath, name), isKnockBack_(false), hp_(MAX_HP), hTime_(ZERO)
{
}

//更新の前に一回呼ばれる関数
void BossEnemy::EnemyChildStartUpdate()
{
	/////////////////タイマー追加/////////////////

	ARGUMENT_INITIALIZE(hTime_,Time::Add());

	/////////////////移動速度設定/////////////////

	ARGUMENT_INITIALIZE(moveRatio_,0.25f);

	/////////////////明るさ設定/////////////////

    Model::SetBrightness(hModel_, 1.0f);

	///////////////当たり判定設定///////////////////

	//玉
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * 5, ZERO), COLLIDER_SIZE);
	AddCollider(collision);

	///////////////アニメーション///////////////////

	//開始
	Model::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, ANIM_SPEED);

}

//更新
void BossEnemy::EnemyChildUpdate()
{
	//コライダーのポジション変更
	SetPosCollider(VectorToFloat3((XMVector3Normalize(vNormal_) * 7)));
}

//移動
void BossEnemy::Move()
{
	//アニメーション開始
	Model::SetAnimFlag(hModel_, true);

	//移動して自身のtransformに反映
	transform_.position_ = Float3Add(transform_.position_,
		VectorToFloat3(XMVector3Normalize(XMVector3TransformCoord(front_, transform_.mmRotate_)) * moveRatio_));

	//定数秒以上経過していたら子供生成
	if (Time::GetTimef(hTime_) >= 1.5f)	Generation();

	//高さ合わせるためにレイを飛ばす
	RayCastData downData;
	downData.start = transform_.position_;         //レイのスタート位置
	downData.dir = VectorToFloat3(down_);          //レイの方向
	Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

	//地形の高さに合わせる
	//当たった距離が0.9fより小さいなら
	if (downData.dist < MOVE_RAY_HIT_DISTANCE)
		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&downData.pos) + vNormal_);

	//状態が状態変化の時間より大きくなったら
	if (stateCount_ > operationTime_)
	{
		//0に初期化
		ZERO_INITIALIZE(operationTime_);
		ZERO_INITIALIZE(stateCount_);

		//状態を回転に設定
		ChangeEnemyState(EnemyStateList::GetEnemyRotationState());

		//タイマーリセット
		Time::Reset(hTime_);
		Time::Lock(hTime_);

		//アニメーション停止
		Model::SetAnimFlag(hModel_, false);
	}
}

//回転
void BossEnemy::Rotation()
{
	//アニメーション停止
	Model::SetAnimFlag(hModel_, false);

	//回転
	angle_ += ADD_ROTATION_ANGLE * rotationSign_;
	rotationTotal_ += ADD_ROTATION_ANGLE;

	//回転角度より回転総数が多くなったら
	if (abs(rotationTotal_) > abs(rotationAngle_))
	{
		//0に初期化
		ZERO_INITIALIZE(operationTime_);
		ZERO_INITIALIZE(rotationTotal_);
		ZERO_INITIALIZE(rotationAngle_);

		//タイマースタート
		Time::UnLock(hTime_);

		//状態を待機に設定
		ChangeEnemyState(EnemyStateList::GetEnemyMoveState());
	}
}

//ノックバックして死亡
void BossEnemy::KnockBackDie()
{
	//ノックバックしていないのなら
	if (!isKnockBack_)
	{
		//ノックバックどこまでするか設定(単位ベクトルにして定数分倍にする)
		knockBackDir_ = (-XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * KNOCKBACK_ASSUMPTION_DISTANCE) + XMLoadFloat3(&transform_.position_);

		//ノックバックした
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);
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
		//死亡状態に変更
		ChangeEnemyState(EnemyStateList::GetEnemyDieState());
	}

	//ノックバックした距離がノックバックの想定距離と1以内の距離なら
	if (dist < KNOCKBACK_DIFFERENCIAL_DISTANCE)
	{
		//ノックバックしていない状態にする
		ARGUMENT_INITIALIZE(isKnockBack_, !isKnockBack_);

		//死んでいたら
		if (hp_ <= ZERO)
		{
			//死亡状態に変更
			ChangeEnemyState(EnemyStateList::GetEnemyDieState());
		}
		else
			//待機状態に変更
			ChangeEnemyState(EnemyStateList::GetEnemyRotationState());
	}
}

//死亡
void BossEnemy::Die()
{
	//待機状態に変更
	ChangeEnemyState(EnemyStateList::GetEnemyWaitState());

	//死ぬエフェクト
	EnemyEffectManager::DieEffect(transform_.position_, up_);

	//削除
	KillMe();
}

//生成
void BossEnemy::Generation()
{
	//生成
	Instantiate<BossEnemyChild>(GetParent())->SetPosition(Model::GetBonePosition(hModel_,"Base"));

	//タイマーリセット
	Time::Reset(hTime_);
}


//何かのオブジェクトに当たった時に呼ばれる関数
void BossEnemy::TimeMethod()
{
	Enter();
}

//何かのオブジェクトに当たった時に呼ばれる関数
void BossEnemy::OnCollision(GameObject* pTarget)
{
	//飛ぶボールと当たったかつノックバックしてないかつボールが飛んでいたなら
	if (pTarget->GetObjectName() == "FlyBall" && EnemyStateList::GetEnemyKnockBackState() != pState_ && ((FlyBall*)pTarget)->IsFly())
	{
		//体力減少
		hp_ -= 1;

		//アニメーション停止
		Model::SetAnimFlag(hModel_, false);

		//ヒットストップ演出(すこしゆっくりに)
		Leave();
		pTarget->Leave();

		//Playerも敵も0.15秒後に動き出す
		SetTimeMethod(HIT_STOP_TIME);
		pTarget->SetTimeMethod(HIT_STOP_TIME);

		//当たった位置を調べる
		XMFLOAT3 hitPos = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&transform_.position_)) * GetColliderRadius()));

		//エフェクト表示
		EnemyEffectManager::HitEffect(hitPos, transform_.position_);

		//カメラ振動
		Camera::SetCameraVibration(VIBRATION_INTENSITY);

		//ノックバックして死亡させる
		ChangeEnemyState(EnemyStateList::GetEnemyKnockBackState());

		//終了
		return;
	}
}
