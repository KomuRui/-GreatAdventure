#include "Pipe.h"

//コンストラクタ
Pipe::Pipe(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/Pipe.fbx", "Pipe")
{
}

//更新の前に一度だけ飛ばれる関数
void Pipe::ChildStartUpdate()
{
}

//更新
void Pipe::ChildUpdate()
{
}
