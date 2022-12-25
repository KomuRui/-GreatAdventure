#include "Block.h"
#include "../Engine/Model.h"

//コンストラクタ
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name), isHit_(false), hitMovePos_(0, 0, 0), initialPos_(0, 0, 0)
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
	//当たった時のポジション設定(半径分上に)
	hitMovePos_ = VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal_) * 0.5));

	//初期値のポジション設定
	initialPos_ = transform_.position_;

	//レイの当たり判定になるように設定
	Model::SetRayFlag(hModel_, true);

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
	transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), 0.20));

	//距離が0.1より小さいなら次の目的地を設定
	if (RangeCalculation(transform_.position_, hitMovePos_) < 0.1)
	{
		//往復が終わっているなら
		if (count_ == 1)
		{
			//保存しておく
			XMFLOAT3 KeepPos = initialPos_;

			//すべて初期状態にしておく
			transform_.position_ = hitMovePos_;
			isHit_ = false;
			initialPos_ = hitMovePos_;
			hitMovePos_ = KeepPos;
			count_ = 0;
		}
		else
		{
			//保存しておく
			XMFLOAT3 KeepPos = hitMovePos_;

			//目的地変更
			transform_.position_ = hitMovePos_;
			hitMovePos_ = initialPos_;
			initialPos_ = KeepPos;
			count_++;
		}
	}
}

