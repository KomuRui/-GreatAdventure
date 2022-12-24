#include "Stage.h"
#include "Block/Block.h"

//コンストラクタ
Stage::Stage(GameObject* parent, std::string name)
	:GameObject(parent,name), warpPos_(0,0,0)
{
}

//定数
namespace
{
	static float BLOCK_SIZE = 1.0f;				    //ブロックのサイズ
	static const float PLAYER_MODEL_SIZE_X = 1.0f;  //PlayerのXのモデルサイズ
	static const float PLAYER_MODEL_SIZE_Y = 2.0f;  //PlayerのYのモデルサイズ
}

//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
bool Stage::IsBlock(XMFLOAT3* pos, int status)
{
	//連想for文
	for (const auto& block : tBlock_)
	{
		//ポジションとサイズを変数に入れておく
		XMFLOAT3 p = block->GetPosition();
		XMFLOAT3 s = block->GetScale();

		//もし当たっていたら
		if (p.x + (BLOCK_SIZE * s.x) > pos->x &&
			p.x - (BLOCK_SIZE * s.x) < pos->x &&
			p.y - (BLOCK_SIZE * s.y) < pos->y &&
			p.y + (BLOCK_SIZE * s.y) > pos->y &&
			p.z - (BLOCK_SIZE * s.z) < pos->z &&
			p.z + (BLOCK_SIZE * s.z) > pos->z)
		{

			//方向によって処理を分ける
			switch (status)
			{
			//右
			case Right:
				pos->x = (p.x + (PLAYER_MODEL_SIZE_X / 2) + (BLOCK_SIZE * s.x));
				break;

			//左
			case Left:
				pos->x = (p.x - (PLAYER_MODEL_SIZE_X / 2) - (BLOCK_SIZE * s.x));
				break;

			//下
			case Under:
				pos->y = (p.y + (PLAYER_MODEL_SIZE_Y / 2) + (BLOCK_SIZE * s.y));
				break;

			//上
			case Top:
				pos->y = (p.y - (PLAYER_MODEL_SIZE_Y / 2) - (BLOCK_SIZE * s.y));
				block->SetIsHit(true);
				break;
			}

			return true;
		}
	}

	return false;
}