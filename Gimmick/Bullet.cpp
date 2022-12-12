#include "Bullet.h"
#include "../Engine/Model.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"), hModel_(-1), front_(XMVectorSet(0,0,1,0)), speed_(0.5f), lifeTimeCount_(0)
{
}

//初期化
void Bullet::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/Gimmick/Bullet.fbx");
	assert(hModel_ >= 0);

	//////////////////当たり判定設定//////////////////////

	SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	///////////////////transform////////////////////

	transform_.scale_ = { 2,2,2 };
}

//更新の前に一回呼ばれる関数
void Bullet::StartUpdate()
{
}

//更新
void Bullet::Update()
{
	//回転
	transform_.rotate_.y += 5.0;

	//移動
	transform_.position_ = Transform::VectorToFloat3(XMLoadFloat3(&transform_.position_) + (front_ * speed_));

	//生存時間より生きていたら
	if (lifeTimeCount_ > LIFE_TIME)
		KillMe();
	else
		lifeTimeCount_++;
}

//描画
void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void Bullet::Release()
{
}
