#include "UserPlanetBase.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

////定数
namespace
{
	static const float ROTATION_SPEED = 0.1f;			 //回転速度
	static const float STATUS_CHANGE_DISTANCE = 0.05f;   //状態が変更するときの距離
	static const float INTERPOLATION_COEFFICIENT = 0.1f; //補間係数
	static const float FALL_SPEED = 0.4f;                //落ちる速度の値
	static const float KILL_VALUE = -20.0f;              //削除するときの値
}

//コンストラクタ
UserPlanetBase::UserPlanetBase(GameObject* parent, std::string modelPath, std::string name)
	:GameObject(parent, name), hModel_(-1), ModelNamePath_(modelPath), status_(PlanetStatus::Stop), isSelect_(false)
{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void UserPlanetBase::Initialize()
{
	//モデルデータロード
	hModel_ = Model::Load(ModelNamePath_);
	assert(hModel_ >= ZERO);

	//継承先用
	ChildInitialize();
}

//更新の前に一回呼ばれる関数
void UserPlanetBase::StartUpdate()
{
}

//更新
void UserPlanetBase::Update()
{
	//少し回転させる
	transform_.rotate_.y += ROTATION_SPEED;

	//状態によって呼ぶ関数分ける
	switch (status_)
	{
	//移動
	case PlanetStatus::Move:

		NextPositionToMove();
		break;

	//落ちる
	case PlanetStatus::Fall:

		Fall();
		break;

	default:
		break;
	}


	//継承先用
	ChildUpdate();
}

//描画
void UserPlanetBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//解放
void UserPlanetBase::Release()
{
}

/////////////////////関数//////////////////////

//次の位置へ移動
void UserPlanetBase::NextPositionToMove()
{
	//補間しながら目的のポジションまで変更していく
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&nextPos_), INTERPOLATION_COEFFICIENT));
	
	//距離が0.05より小さいならStop状態に設定
	if (RangeCalculation(transform_.position_, nextPos_) < STATUS_CHANGE_DISTANCE)
	{
		//自身のポジションを次の位置に設定
		ARGUMENT_INITIALIZE(transform_.position_, nextPos_);
		ARGUMENT_INITIALIZE(status_, PlanetStatus::Stop);
	}

}

//次のポジションセット
void UserPlanetBase::SetNextPosition(const XMFLOAT3& nextPos)
{
	ARGUMENT_INITIALIZE(nextPos_, nextPos);           //次の位置設定
	ARGUMENT_INITIALIZE(status_, PlanetStatus::Move); //状態設定
}

//選択されていないのなら落ちる
void UserPlanetBase::Fall()
{
	//選択されていないのなら
	if (!isSelect_)
	{
		//落とす
		transform_.position_.y -= FALL_SPEED;

		//もし削除する値より下なら削除
		if (transform_.position_.y < KILL_VALUE) KillMe();
	}
}

//選択されているかどうか
bool UserPlanetBase::IsSelect()
{
	//もし選択されているのなら
	if (isSelect_)
	{
		//選択解除
		ARGUMENT_INITIALIZE(isSelect_, false);
		return true;
	}

	return false;
}