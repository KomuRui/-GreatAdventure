#include "Posture.h"

//定数
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//レイの当たった距離
	static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045f;//法線を補間するときの補間係数
	static const int MAX_NORMAL_RADIANS = 50;               //法線との最大角度
}

//コンストラクタ
Posture::Posture()
{
	ARGUMENT_INITIALIZE(transform_,nullptr);
	ARGUMENT_INITIALIZE(down_,nullptr);
	ARGUMENT_INITIALIZE(vNormal_,nullptr);
	ARGUMENT_INITIALIZE(hGroundModel_, (int)ZERO);
}

//更新
void Posture::Update()
{
	//複数個所で使うので先に宣言しておく
	RayCastData downData;
	downData.start = transform_->position_;        //レイのスタート位置
	downData.dir = VectorToFloat3(*down_);         //レイの方向
	Model::AllRayCast(hGroundModel_, &downData);   //レイを発射(All)

	 //真下の法線を調べてキャラの上軸を決定する
	CheckUnderNormal(downData);

	//ステージとの当たり判定
	StageRayCast(downData);
}

//真下の法線を調べてキャラの上軸を決定する
void Posture::CheckUnderNormal(const RayCastData& data)
{
	if (data.hit && (XMVectorGetX(*vNormal_) != XMVectorGetX(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetY(-(*vNormal_)) != XMVectorGetY(XMVector3Normalize(XMLoadFloat3(&data.normal))) || XMVectorGetZ(-(*vNormal_)) != XMVectorGetZ(XMVector3Normalize(XMLoadFloat3(&data.normal)))))
	{
		//元のキャラの上ベクトルvNormalと下の法線の内積を求める
		float dotX = XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMLoadFloat3(&data.normal)), XMVector3Normalize(*vNormal_)));

		//角度が50度以内に収まっていたら(壁とかに上らせないため)
		if (acos(dotX) < XMConvertToRadians(MAX_NORMAL_RADIANS) && acos(dotX) > XMConvertToRadians(-MAX_NORMAL_RADIANS))
		{
			//ちょっと補間
			*vNormal_ = XMVector3Normalize((XMVectorLerp(XMVector3Normalize(*vNormal_), XMLoadFloat3(&data.normal), NORMAL_INTERPOLATION_FACTOR)));
			*down_ = -(*vNormal_);
		}
	}
}

//レイで当たり判定(3D用)
void Posture::StageRayCast(const RayCastData& data)
{
	//////////////////////////////はみ出した分下げる//////////////////////////////////////

	//下の距離が1.0以上かつ重力適用するなら
	if (data.dist >= RAY_HIT_DISTANCE)
	{
		transform_->position_ = Float3Add(transform_->position_, VectorToFloat3((-(*vNormal_)) * GRAVITY_STRENGTH));
	}
}
