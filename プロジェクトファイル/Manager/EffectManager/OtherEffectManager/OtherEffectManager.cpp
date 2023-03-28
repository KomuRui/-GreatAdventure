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
		data.speedRnd = 0.8f;
		data.size = XMFLOAT2(1.8f, 1.8f);
		data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
		data.scale = XMFLOAT2(1.05f, 1.05f);
		data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
		data.deltaColor = XMFLOAT4(0.0f, -1.0f / 105.0f, 0.0f, -1.0f / 105.0f);
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
		data.gravity = 0.005f;
		data.speed = 0.3f;
		data.accel = 0.98f;
		data.speedRnd = 0.0f;
		data.size = XMFLOAT2(2.0f, 2.0f);
		data.sizeRnd = XMFLOAT2(0.8f, 0.4f);
		data.scale = XMFLOAT2(1.02f, 1.02f);
		data.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.1f);
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
		data.gravity = 0.005f;
		data.speed = 0.3f;
		data.accel = 0.98f;
		data.speedRnd = 0.0f;
		data.size = XMFLOAT2(0.2f, 0.2f);
		data.sizeRnd = XMFLOAT2(0.0f, 0.0f);
		data.scale = XMFLOAT2(0.98f, 0.98f);
		data.color = XMFLOAT4(0.5f, 1.0f, 1.0f, 1.0f);
		VFX::Start(data);

		return handle;
	}
}