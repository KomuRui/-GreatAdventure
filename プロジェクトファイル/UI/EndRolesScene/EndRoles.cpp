#include "EndRoles.h"

//定数
namespace
{
	static const float MOVE_RANGE = 13.4f;      //移動できる範囲
	static const float START_Y_POS = -13.0f;	//初期
	static const float MOVE_ADD_VALUE = 0.008f; //移動するときの加算量
}

//コンストラクタ
EndRoles::EndRoles(GameObject* parent, std::string modelPath, std::string name)
	: ImageBase(parent, modelPath, name)
{
}

//更新の前に一度だけ呼ばれる
void EndRoles::ChildStartUpdate()
{
	//初期位置
	ARGUMENT_INITIALIZE(transform_.position_.y,START_Y_POS);
}

//更新
void EndRoles::ChildUpdate()
{
	//移動範囲内なら移動
	if(transform_.position_.y < MOVE_RANGE) transform_.position_.y += MOVE_ADD_VALUE;
}