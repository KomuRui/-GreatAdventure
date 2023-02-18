#include "Bullet.h"
#include "../Engine/Model.h"

//定数
namespace
{
	static const int LIFE_TIME = 180;						 //生存時間
	static const float ADD_ROTATION_ANGLE = 5.0f;            //回転するときに加算する角度
	static const float SPEED = 1.0f;                         //球のスピード
	static const float    COLLIDER_SIZE = 2.0f;				 //コライダーのサイズ
	static const XMFLOAT3 COLLIDER_POS = { ZERO,ZERO,ZERO }; //コライダーの位置
	static const XMFLOAT3 BULLET_SCALE = { 4,4,4 };          //球の拡大率
}

//コンストラクタ
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"), hModel_(-1), front_(XMVectorSet(ZERO, ZERO,1, ZERO)),lifeTimeCount_(ZERO)
{
}

//初期化
void Bullet::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Stage/Gimmick/Bullet.fbx");
	assert(hModel_ >= ZERO);

	//////////////////当たり判定設定//////////////////////

	SphereCollider* collision = new SphereCollider(COLLIDER_POS, COLLIDER_SIZE);
	AddCollider(collision);

	///////////////////transform////////////////////

	ARGUMENT_INITIALIZE(transform_.scale_, BULLET_SCALE);
}

//更新の前に一回呼ばれる関数
void Bullet::StartUpdate()
{
}

//更新
void Bullet::Update()
{
	//回転
	transform_.rotate_.y += ADD_ROTATION_ANGLE;

	//移動
	transform_.position_ = VectorToFloat3(XMLoadFloat3(&transform_.position_) + (front_ * SPEED));

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
