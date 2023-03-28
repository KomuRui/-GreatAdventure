#include "CoinEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// Coinのエフェクトを管理する
/// </summary>
namespace CoinEffectManager
{

	//当たった時のエフェクト
	void HitEffect()
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = GameManager::GetpPlayer()->GetPosition();
		data.delay = 0;
		data.number = 150;
		data.lifeTime = 100;
		data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
		data.direction = VectorToFloat3(GameManager::GetpPlayer()->GetNormal());
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedRnd = 1;
		data.accel = 0.93f;
		data.size = XMFLOAT2(0.1f, 0.1f);
		data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
		data.scale = XMFLOAT2(0.99f, 0.99f);
		data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
		data.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		data.gravity = 0.003f;
		VFX::Start(data);
	}

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	/// <param name="pos">発生させたい位置</param>
	void HitEffect(XMFLOAT3 pos)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 150;
		data.lifeTime = 100;
		data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
		data.direction = VectorToFloat3(GameManager::GetpPlayer()->GetNormal());
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedRnd = 1;
		data.accel = 0.93f;
		data.size = XMFLOAT2(0.1f, 0.1f);
		data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
		data.scale = XMFLOAT2(0.99f, 0.99f);
		data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
		data.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		data.gravity = 0.003f;
		VFX::Start(data);
	}
}