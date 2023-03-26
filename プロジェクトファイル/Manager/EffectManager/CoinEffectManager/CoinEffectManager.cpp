#include "CoinEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// Coin�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace CoinEffectManager
{

	//�����������̃G�t�F�N�g
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
		data.accel = 0.93;
		data.size = XMFLOAT2(0.1, 0.1);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		VFX::Start(data);
	}

	/// <summary>
	/// �����������̃G�t�F�N�g
	/// </summary>
	/// <param name="pos">�������������ʒu</param>
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