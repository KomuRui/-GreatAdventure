#include "Block.h"
#include "../Engine/Model.h"

//定数
namespace
{
	static const float INTERPOLATION_COEFFICIENT = 0.2f;	//補間係数
	static const float HIT_ADD_LENGTH = 0.5f;				//当たった時に加算する長さ
	static const float TARGET_CHANGE_DISTANCE = 0.1f;       //目的地を変える距離
}

//コンストラクタ
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isHit_(false), hitMovePos_(ZERO, ZERO, ZERO), initialPos_(ZERO, ZERO, ZERO), roundTripEnd_(false)
{
}

//初期化
void Block::ChildInitialize()
{
	//継承先用
	BlockChildInitialize();
}

//更新の前に一度だけ呼ばれる関数
void Block::ChildStartUpdate()
{
	//当たった時の移動先ポジション設定(半径分上に)
	hitMovePos_ = VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal_) * HIT_ADD_LENGTH));

	//初期値のポジション設定
	ARGUMENT_INITIALIZE(initialPos_,transform_.position_);

	//レイの当たり判定になるように設定
	Model::SetRayFlag(hModel_, true);

	//自身を追加
	Model::SetBlockObj(hModel_, this);

	//継承先用
	BlockChildStartUpdate();
}

//更新
void Block::ChildUpdate()
{
	//当たっているなら関数呼び出す
	if (isHit_) HitToLowerPlayer();

	//継承先用
	BlockChildUpdate();
}

//描画
void Block::ChildDraw()
{
	//継承先用
	BlockChildDraw();
}

//Playerが下から当たった時の挙動
void Block::HitToLowerPlayer()
{
	//補間しながら目的のポジションまで変更していく
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), INTERPOLATION_COEFFICIENT));

	//距離が0.1より小さいなら次の目的地を設定
	if (RangeCalculation(transform_.position_, hitMovePos_) < TARGET_CHANGE_DISTANCE)
	{
		//往復が終わっているなら
		if (roundTripEnd_)
		{
			//保存しておく
			XMFLOAT3 KeepPos = initialPos_;

			//すべて初期状態にしておく
			ARGUMENT_INITIALIZE(transform_.position_,hitMovePos_);
			ARGUMENT_INITIALIZE(isHit_,false);
			ARGUMENT_INITIALIZE(initialPos_,hitMovePos_);
			ARGUMENT_INITIALIZE(hitMovePos_,KeepPos);
			ARGUMENT_INITIALIZE(roundTripEnd_,false);
		}
		else
		{
			//保存しておく
			XMFLOAT3 KeepPos = hitMovePos_;

			//目的地変更
			ARGUMENT_INITIALIZE(transform_.position_,hitMovePos_);
			ARGUMENT_INITIALIZE(hitMovePos_,initialPos_);
			ARGUMENT_INITIALIZE(initialPos_,KeepPos);
			ARGUMENT_INITIALIZE(roundTripEnd_,true);
		}
	}

	//継承先用の挙動
	BlockChildHitToLowerPlayer();
}

