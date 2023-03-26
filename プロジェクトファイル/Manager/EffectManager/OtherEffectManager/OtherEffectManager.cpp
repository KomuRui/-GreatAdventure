#include "OtherEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// 様々なエフェクトを管理する
/// </summary>
namespace OtherEffectManager
{
	//爆発エフェクト
	void ExplosionEffect(const XMFLOAT3& pos)
	{
		EmitterData data;

		//炎
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 180;
		data.lifeTime = 240;
		data.direction = XMFLOAT3(0, 1, 0);
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.6f;
		data.speedRnd = 0.8;
		data.size = XMFLOAT2(1.8, 1.8);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, -1.0 / 105, 0, -1.0 / 105);
		VFX::Start(data);
	}

	//水流エフェクト
	int WaterCurrentEffect(const XMFLOAT3& pos, const XMFLOAT3& dir)
	{
		EmitterData data;

		data.textureFileName = "Image/Effect/Water.png";
		data.position = pos;
		data.delay = 1;
		data.number = 3;
		data.lifeTime = 150;
		data.direction = dir;
		data.directionRnd = XMFLOAT3(0, 0, 0);
		data.gravity = 0.005;
		data.speed = 0.3f;
		data.accel = 0.98;
		data.speedRnd = 0.0;
		data.size = XMFLOAT2(2, 2);
		data.sizeRnd = XMFLOAT2(0.8, 0.4);
		data.scale = XMFLOAT2(1.02, 1.02);
		data.color = XMFLOAT4(1, 1, 1, 0.1);
		int handle = VFX::Start(data);

		//水滴
		data.textureFileName = "Image/Effect/defaultParticle.png";
		data.position = pos;
		data.positionRnd = XMFLOAT3(0.5, 0, 0);
		data.delay = 1;
		data.number = 3;
		data.lifeTime = 50;
		data.direction = dir;
		data.directionRnd = XMFLOAT3(0, 20, 0);
		data.gravity = 0.005;
		data.speed = 0.3f;
		data.accel = 0.98;
		data.speedRnd = 0.0;
		data.size = XMFLOAT2(0.2, 0.2);
		data.sizeRnd = XMFLOAT2(0, 0);
		data.scale = XMFLOAT2(0.98, 0.98);
		data.color = XMFLOAT4(0.5, 1, 1, 1);
		VFX::Start(data);

		return handle;
	}
}