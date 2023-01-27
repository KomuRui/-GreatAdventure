#include "Pipe.h"
#include "../Manager/GameManager/GameManager.h"

//定数
namespace
{
	//死亡する時のPlayerとのZの距離
	static const int KILLME_PLAYER_Z_DIS = -5;
}

//コンストラクタ
Pipe::Pipe(GameObject* parent)
	:Mob(parent, "Stage/Gimmick/Pipe.fbx", "Pipe")
{
}

//更新の前に一度だけ飛ばれる関数
void Pipe::ChildStartUpdate()
{
	///////////////明るさ///////////////////

	Model::SetBrightness(hModel_, 1.0f);
}

//更新
void Pipe::ChildUpdate()
{
	//Playerより後ろに行ったら死亡
	if (transform_.position_.z < GameManager::GetpPlayer()->GetPosition().z + KILLME_PLAYER_Z_DIS)
		KillMe();
}
