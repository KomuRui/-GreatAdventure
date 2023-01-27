#include "TurnCircle.h"
#include "../Engine/Model.h"
#include "../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//レイの当たった距離
	static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
	static const float ADD_ROTATION_VALUE = 0.05f;          //回転するときの加算する角度
	static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
	static const int KILLME_PLAYER_Z_DIS = -5;              //死亡する時のPlayerとのZの距離
}

//コンストラクタ
TurnCircle::TurnCircle(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/TurnCircle.fbx", "TurnCircle"), rotationAngle_(ZERO)
{
}

//更新の前に一度だけ飛ばれる関数
void TurnCircle::ChildStartUpdate()
{
}

//更新
void TurnCircle::ChildUpdate()
{
	//複数個所で使うので先に宣言しておく
	RayCastData downData;
	downData.start = transform_.position_;         //レイのスタート位置
	downData.dir = VectorToFloat3(down_);          //レイの方向
	Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

	 //真下の法線を調べてキャラの上軸を決定する
	CheckUnderNormal(downData);

	//ステージとの当たり判定
	StageRayCast(downData);

	//回転
	Rotation();

	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z + KILLME_PLAYER_Z_DIS)
		KillMe();
}

//回転
void TurnCircle::Rotation()
{
	//回転
	transform_.mmRotate_ *= XMMatrixRotationAxis(STRAIGHT_VECTOR, rotationAngle_);

	//Angleが360までいったら0に戻す
	if (rotationAngle_ > TWOPI_DEGREES)
		rotationAngle_ = ZEROPI_DEGREES;

	//加算
	rotationAngle_ += ADD_ROTATION_VALUE;
}

//真下の法線を調べてキャラの上軸を決定する
void TurnCircle::CheckUnderNormal(const RayCastData& data)
{
	if (data.hit && (XMVectorGetX(vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-vNormal_) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-vNormal_) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
	{
		//元のキャラの上ベクトルvNormalと下の法線の内積を求める
		float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(vNormal_)));

		//角度が50度以内に収まっていたら(壁とかに上らせないため)
		if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
		{
			//ちょっと補間
			vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
			down_ = -vNormal_;
		}
	}
}

//レイ(円用)
void TurnCircle::StageRayCast(const RayCastData& data)
{
	//下の距離が1.0以上かつ重力適用するなら
	if (data.dist >= RAY_HIT_DISTANCE)
	{
		transform_.position_ = Float3Add(transform_.position_, VectorToFloat3((-vNormal_) * GRAVITY_STRENGTH));
	}

}