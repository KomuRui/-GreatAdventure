#include "EnemyEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// Enemyのエフェクトを管理する
/// </summary>
namespace EnemyEffectManager
{
	

	//当たった時のエフェクト
	void HitEffect(const XMFLOAT3& Hitpos, const XMFLOAT3& pos)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = Hitpos;
		data.delay = 0;
		data.number = 40;
		data.lifeTime = 40;
		XMStoreFloat3(&data.direction, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&pos)));
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.15f;
		data.speedRnd = 0.8;
		data.size = XMFLOAT2(1.5, 1.5);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
		VFX::Start(data);
	}

	//死ぬときのエフェクト
	void DieEffect(const XMFLOAT3& pos, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 250;
		data.lifeTime = 100;
		data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
		data.direction = VectorToFloat3(dir);
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedRnd = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.1, 0.1);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		VFX::Start(data);
	}
}