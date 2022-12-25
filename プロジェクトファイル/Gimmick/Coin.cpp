#include "Coin.h"

//定数
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.08f; //回転するときの加算する角度
	static const float COLLIDER_POS_Y = 1.0f;      //コライダーのY軸のポジション
	static const float COLLIDER_RADIUS = 1.0f;     //コライダーの半径
}

//更新の前に一度だけ呼ばれる関数
void Coin::ChildStartUpdate()
{
	//コライダー追加
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, XMVectorGetY(XMVector3Normalize(vNormal_)) * COLLIDER_POS_Y * transform_.scale_.y, ZERO), COLLIDER_RADIUS * transform_.scale_.y);
	AddCollider(collision);
}

void Coin::ChildUpdate()
{
	//回転
	angle_ += ADD_ROTATION_ANGLE;

	//Angleが360までいったら0に戻す
	if (angle_ > TWOPI_DEGREES)
		angle_ = ZEROPI_DEGREES;
}

//当たり判定
void Coin::OnCollision(GameObject* pTarget)
{
	//Player以外なら何もしない
	if (pTarget->GetObjectName() != "Player")
		return;

	//自身の削除
	KillMe();
}
