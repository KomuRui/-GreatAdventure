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
	static float BLOCK_SIZE = 1.0f; //ブロックのサイズ
}

//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
bool Stage::IsBlock(XMFLOAT3* pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i)->GetPosition().x + (BLOCK_SIZE * (*i)->GetScale().x) > pos->x &&
			(*i)->GetPosition().x - (BLOCK_SIZE * (*i)->GetScale().x) < pos->x &&
			(*i)->GetPosition().y - (BLOCK_SIZE * (*i)->GetScale().y) < pos->y &&
			(*i)->GetPosition().y + (BLOCK_SIZE * (*i)->GetScale().y) > pos->y &&
			(*i)->GetPosition().z - (BLOCK_SIZE * (*i)->GetScale().z) < pos->z &&
			(*i)->GetPosition().z + (BLOCK_SIZE * (*i)->GetScale().z) > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i)->GetPosition().x + 1.5f);
				break;
			case 1:
				pos->x = ((*i)->GetPosition().x - 1.5f);
				break;
			case 2:
				pos->y = ((*i)->GetPosition().y + 2.0f);
				break;
			case 3:
				pos->y = ((*i)->GetPosition().y - 2.0f);
				(*i)->SetIsHit(true);
				break;
			}

			return true;
		}
	}

	return false;
}