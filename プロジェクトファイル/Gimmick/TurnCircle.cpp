#include "TurnCircle.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Manager/GameManager/GameManager.h"

//定数
namespace
{
	static const float RAY_HIT_DISTANCE = 1.0f;				//レイの当たった距離
	static const float GRAVITY_STRENGTH = 0.083f;           //重力の強さ
	static const float NORMAL_INTERPOLATION_FACTOR = 0.045f;//法線を補間するときの補間係数
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
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);

	///////////障害物として追加///////////

	Model::SetRayFlag(hModel_, true);
	Model::SetObstacleObj(hModel_, this);

	//////////////////////コンポーネントの初期設定////////////////////////////////

	ARGUMENT_INITIALIZE(posture_.transform_, &transform_);
	ARGUMENT_INITIALIZE(posture_.down_, &down_);
	ARGUMENT_INITIALIZE(posture_.vNormal_, &vNormal_);
	ARGUMENT_INITIALIZE(posture_.hGroundModel_, hGroundModel_);
}

//更新
void TurnCircle::ChildUpdate()
{
	//コンポーネントの更新を呼ぶ
	posture_.Update();

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