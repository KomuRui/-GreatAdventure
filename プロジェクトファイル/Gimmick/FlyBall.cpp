#include "FlyBall.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/EffectManager/EnemyEffectManager/EnemyEffectManager.h"
#include "../Engine/Easing.h"

//定数
namespace
{
	static const float ADD_ROTATION_VALUE = 0.05f;   //回転するときの加算値
	static const float MAX_ROTATION_VALUE = 100.0f;  //最大回転値
	static const float COLLIDER_POS_Y = 1.0f;        //コライダーのY軸のポジション
	static const float COLLIDER_RADIUS = 1.0f;       //コライダーの半径
}

//コンストラクタ
FlyBall::FlyBall(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent,modelPath,name), rotateAngle_(ZERO),isFly_(false), pEasing_(new EasingMove), basePos_(ZERO,ZERO,ZERO), isReturnPos(false)
{}

//更新の前に一度だけ呼ばれる関数
void FlyBall::ChildStartUpdate()
{
	//コライダー追加
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS);
	AddCollider(collision);

	//明るさ
	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void FlyBall::ChildUpdate()
{
	//ギミックの上軸で回転させる
	transform_.mmRotate_ *= XMMatrixRotationAxis(up_, rotateAngle_);

	//回転させる
	rotateAngle_ += ADD_ROTATION_VALUE;

	//定数以上になったら初期化
	if (rotateAngle_ >= MAX_ROTATION_VALUE) ARGUMENT_INITIALIZE(rotateAngle_,ZERO);

	//もし飛んでいるのなら
	if (isFly_) Fly();
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

			//動き設定
			pEasing_->Reset(&transform_.position_,transform_.position_, basePos_, 0.5f, Easing::OutQuad);
		}
		else
		{
			ARGUMENT_INITIALIZE(isFly_,false);
			ARGUMENT_INITIALIZE(isReturnPos,false);
		}
	}
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
		ARGUMENT_INITIALIZE(basePos_, transform_.position_);

		//動き設定
		pEasing_->Reset(&transform_.position_, transform_.position_, afterPos, 0.5f, Easing::OutQuad);

		//当たった時のエフェクト表示
		EnemyEffectManager::HitEffect(Float3Add(GameManager::GetpPlayer()->GetPosition(), VectorToFloat3(dir_ * 0.5f)), transform_.position_);

	}
}