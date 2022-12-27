#include "ItemBlock.h"

//定数
namespace
{
	static const float ADD_ROTATION_ANGLE = 0.05f; //回転するときに加算する角度
}

//コンストラクタ
ItemBlock::ItemBlock(GameObject* parent, std::string modelPath, std::string name)
	: Block(parent, modelPath, name), type_(ItemBlockNormal)
{
}

//更新
void ItemBlock::BlockChildUpdate()
{
	//もし型がRotationなら
	if (type_ == ItemBlockRotation) Move();
}

//ブロックの動き
void ItemBlock::Move()
{
	angle_ += ADD_ROTATION_ANGLE;
}
