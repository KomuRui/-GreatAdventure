#include "MoveFloor.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"

//コンストラクタ
MoveFloor::MoveFloor(GameObject* parent, std::string modelPath, std::string name) :Mob(parent, modelPath, name), status_(STOP)
,number_(0)
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

	MoveFloorTarget_ = { 31, 20.14928, -15.2083 };
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

	//移動
	XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&MoveFloorTarget_), 0.03));

	//今のポジションと目的地の距離を求める
	float dist = RangeCalculation(transform_.position_, MoveFloorTarget_);

	//距離が0.5より小さいならターゲット変える
	if (dist < 0.5)
	{
		transform_.position_ = MoveFloorTarget_;
		MoveFloorTarget_ = target;
		target = transform_.position_;
	}

}