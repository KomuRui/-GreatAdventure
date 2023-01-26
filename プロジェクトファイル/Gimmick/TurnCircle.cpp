#include "TurnCircle.h"

//コンストラクタ
TurnCircle::TurnCircle(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/TurnCircle.fbx", "TurnCircle")
{
}

//更新の前に一度だけ飛ばれる関数
void TurnCircle::ChildStartUpdate()
{
}

//更新
void TurnCircle::ChildUpdate()
{
}
