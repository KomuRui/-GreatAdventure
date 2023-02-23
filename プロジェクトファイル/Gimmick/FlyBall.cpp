#include "FlyBall.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/ResourceManager/Easing.h"

//定数
namespace
{
	static const float ADD_ROTATION_VALUE = 0.05f;   //回転するときの加算値
	static const float MAX_ROTATION_VALUE = 100.0f;  //最大回転値
	static const float HIT_STOP_TIME = 0.15f;		 //ヒットストップ演出の時間
	static const float COLLIDER_POS_Y = 1.0f;        //コライダーのY軸のポジション
	static const float COLLIDER_RADIUS = 1.0f;       //コライダーの半径
}

//コンストラクタ
FlyBall::FlyBall(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name), rotateAngle_(ZERO),isFly_(false), pEasing_(new EasingMove),
	beforePos_(ZERO,ZERO,ZERO), isReturnPos(false), hStickModel_(ZERO), basePos_(ZERO, ZERO, ZERO), baseUp_(XMVectorSet(ZERO, ZERO, ZERO, ZERO))
{}

//更新の前に一度だけ呼ばれる関数
void FlyBall::ChildStartUpdate()
{
	//モデルデータのロード
	hStickModel_ = Model::Load("Stage/Gimmick/FlyBall_Stick.fbx");
	assert(hStickModel_ >= ZERO);

	//ベースのポジションと上ベクトル設定
	ARGUMENT_INITIALIZE(basePos_, transform_.position_);
	ARGUMENT_INITIALIZE(baseUp_, vNormal_);

	//棒のトランスフォーム設定
	ARGUMENT_INITIALIZE(tStick_.position_,transform_.position_);
	ARGUMENT_INITIALIZE(tStick_.scale_, tStick_.scale_);
	ARGUMENT_INITIALIZE(tStick_.mFlag_, true);

	//コライダー追加
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS);
	AddCollider(collision);

	//明るさ
	Model::SetBrightness(hModel_, 1.0f);
	Model::SetBrightness(hStickModel_, 1.0f);
}

//更新
void FlyBall::ChildUpdate()
{
	//回転
	Rotation();

	//もし飛んでいるのなら
	if (isFly_) Fly();

	//棒のトランスフォームの計算
	StickCalculation();
}

//描画
void FlyBall::ChildDraw()
{
	Model::SetTransform(hStickModel_, tStick_);
	Model::Draw(hStickModel_);
}

//飛ぶ
void FlyBall::Fly()
{
	//動かす
	if (pEasing_->Move())
	{
		//戻っていないのなら
		if (!isReturnPos)
		{
			//元に戻す
			ARGUMENT_INITIALIZE(isReturnPos, true);

			//移動前のポジションに戻るように設定
			pEasing_->Reset(&transform_.position_,transform_.position_, beforePos_, 0.5f, Easing::OutQuad);
		}
		else
		{
			ARGUMENT_INITIALIZE(isFly_,false);
			ARGUMENT_INITIALIZE(isReturnPos,false);
		}
	}
}

//回転
void FlyBall::Rotation()
{
	//ギミックの上軸で回転させる
	transform_.mmRotate_ *= XMMatrixRotationAxis(up_, rotateAngle_);

	//回転の値を増やす
	rotateAngle_ += ADD_ROTATION_VALUE;

	//定数以上になったら初期化
	if (rotateAngle_ >= MAX_ROTATION_VALUE) ARGUMENT_INITIALIZE(rotateAngle_, ZERO);
}

//棒のトランスフォームの計算
void FlyBall::StickCalculation()
{
	//棒の回転行列設定
	ARGUMENT_INITIALIZE(tStick_.mmRotate_, transform_.mmRotate_);

	//棒の拡大縮小計算
	ARGUMENT_INITIALIZE(tStick_.scale_.y, RangeCalculation(basePos_, transform_.position_) - 0.3f);

	//Ballのベースポジションから現在のBallのポジションに向けてのベクトルを作成
	XMVECTOR toBall = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&basePos_);

	//ベース上ベクトルとtoBallとの内積を調べる
	float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(baseUp_), XMVector3Normalize(toBall)));

	//外積求める
	XMVECTOR cross = XMVector3Cross(baseUp_, toBall);

	//値の範囲外じゃなければ外積軸で回転させる
	if (dotX != ZERO && dotX <= 1 && dotX >= -1) tStick_.mmRotate_ *= XMMatrixRotationAxis(cross, acos(dotX));
}

//当たり判定
void FlyBall::OnCollision(GameObject* pTarget)
{
	//当たった相手がPlayerじゃないのならこの先の処理をしない
	if (pTarget->GetObjectName() != "Player") return;

	//もしPlayerが回転していたら
	if (GameManager::GetpPlayer()->IsRotation() && !isFly_)
	{
		//飛ばす
		ARGUMENT_INITIALIZE(isFly_, true);

		//飛んでいく方向を計算
		XMVECTOR dir_ = XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(SubTract(transform_.position_, pTarget->GetPosition()))));

		//向き調整
		dir_ += GameManager::GetpPlayer()->GetDown() * 0.5f;

		//飛ぶポジションを設定
		XMFLOAT3 afterPos = Float3Add(VectorToFloat3(dir_ * 15.0f),transform_.position_);

		//元々いたポジション設定
		ARGUMENT_INITIALIZE(beforePos_, transform_.position_);

		//動き設定
		pEasing_->Reset(&transform_.position_, transform_.position_, afterPos, 0.5f, Easing::OutQuad);

		//当たった時のエフェクト表示
		EnemyEffectManager::HitEffect(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(dir_ * 0.5f)), transform_.position_);

		//ヒットストップ演出(すこし止める)
		Leave();
		pTarget->Leave();

		//Playerも敵も0.15秒後に動き出す
		SetTimeMethod(HIT_STOP_TIME);
		pTarget->SetTimeMethod(HIT_STOP_TIME);
	}
}

//指定した時間で呼ばれるメソッド
void FlyBall::TimeMethod()
{
	Enter();
}