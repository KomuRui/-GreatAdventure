#include "EnemyEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"

/// <summary>
/// Enemyのエフェクトを管理する
/// </summary>
namespace EnemyEffectManager
{
	/////////////////////////////////変数/////////////////////////////////////

	//エフェクト表示するのに必要なデータ
	std::vector<Particle*> pEffectData_;

	/////////////////////////////////関数/////////////////////////////////////

	//追加
	int Add(GameObject* enemy)
	{
		//新たに追加
		pEffectData_.push_back(Instantiate<Particle>(enemy));
		return (int)pEffectData_.size() - 1;
	}

	//解放
	void AllRelease()
	{
		//削除
		for (auto i = pEffectData_.begin(); i != pEffectData_.end(); i++)
		{
			(*i)->KillMe();
		}

		//空にする
		pEffectData_.clear();
	}

	//当たった時のエフェクト
	void HitEffect(const int& handle, const XMFLOAT3& Hitpos, const XMFLOAT3& pos)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = Hitpos;
		data.delay = 0;
		data.number = 40;
		data.lifeTime = 40;
		XMStoreFloat3(&data.dir, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&pos)));
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.15f;
		data.speedErr = 0.8;
		data.size = XMFLOAT2(1.5, 1.5);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
		pEffectData_[handle]->Start(data);
	}

	//死ぬときのエフェクト
	void DieEffect(const int& handle, const XMFLOAT3& pos, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 250;
		data.lifeTime = 100;
		data.positionErr = XMFLOAT3(0.5, 0, 0.5);
		data.dir = VectorToFloat3(dir);
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedErr = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.1, 0.1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		pEffectData_[handle]->Start(data);
	}
}