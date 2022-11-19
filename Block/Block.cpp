#include "Block.h"

//コンストラクタ
Block::Block(GameObject* parent, std::string modelPath, std::string name)
	:Mob(parent, modelPath, name),isHit_(false), hitMovePos_(0,0,0)
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
	hitMovePos_ = Transform::VectorToFloat3((XMLoadFloat3(&transform_.position_) + XMVector3Normalize(vNormal) * 0.5));

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
	transform_.position_ = Transform::VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&hitMovePos_), 0.5));
}

