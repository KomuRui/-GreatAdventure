#include "Stage.h"
#include "Block/Block.h"

//コンストラクタ
Stage::Stage(GameObject* parent, std::string name)
	:GameObject(parent,name)
{
}

//そこにブロックがあるかどうか,もしあったら重なっている分ずらす
bool Stage::IsBlock(XMFLOAT3* pos, int status)
{
	for (auto i = tBlock_.begin(); i != tBlock_.end(); i++)
	{
		if ((*i)->GetPosition().x + (1 * (*i)->GetScale().x) > pos->x &&
			(*i)->GetPosition().x - (1 * (*i)->GetScale().x) < pos->x &&
			(*i)->GetPosition().y - (1 * (*i)->GetScale().y) < pos->y &&
			(*i)->GetPosition().y + (1 * (*i)->GetScale().y) > pos->y &&
			(*i)->GetPosition().z - (1 * (*i)->GetScale().z) < pos->z &&
			(*i)->GetPosition().z + (1 * (*i)->GetScale().z) > pos->z)
		{
			switch (status)
			{
			case 0:
				pos->x = ((*i)->GetPosition().x + 1.5);
				break;
			case 1:
				pos->x = ((*i)->GetPosition().x - 1.5);
				break;
			case 2:
				pos->y = ((*i)->GetPosition().y + 2);
				break;
			case 3:
				pos->y = ((*i)->GetPosition().y - 2);
				(*i)->SetIsHit(true);
				break;
			}

			return true;
		}
	}

	return false;
}