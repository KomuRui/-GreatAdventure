#include "MoveFloor.h"
#include "../Engine/ResourceManager/Model.h"
#include "../Engine/GameObject/Camera.h"

//定数
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.03f; //補間係数
	static const float TARGET_CHANGE_DISTANCE = 0.5f;     //目的地を変更するときの距離
}

//コンストラクタ
MoveFloor::MoveFloor(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
{
}

MoveFloor::~MoveFloor()
{
}

//スタートアップデート
void MoveFloor::ChildStartUpdate()
{
	//Playerに当たり判定させるために追加
	Model::SetRayFlag(hModel_, true);

	//次の目的地設定
	MoveFloorTarget_ = { 31.0f, 20.14928f, -15.2083f };
}

//更新
void MoveFloor::ChildUpdate()
{
	//状態がMoveなら
	if (status_ == MOVE) MovingToPurpose();
}

//次の目的地まで移動
void MoveFloor::MovingToPurpose()
{
	//次のターゲット保存しておくための変数
	static XMFLOAT3 target = transform_.position_;

	//補完しながら移動
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&MoveFloorTarget_), INTERPOLATION_COEFFICIENT));

	//今のポジションと目的地の距離を求める
	float dist = RangeCalculation(transform_.position_, MoveFloorTarget_);

	//距離が0.5より小さいならターゲット変える
	if (dist < TARGET_CHANGE_DISTANCE)
	{
		transform_.position_ = MoveFloorTarget_;
		MoveFloorTarget_ = target;
		target = transform_.position_;
	}

}