#include "EnemyEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// Enemy�̃G�t�F�N�g���Ǘ�����
/// </summary>
namespace EnemyEffectManager
{
	

	//�����������̃G�t�F�N�g
	void HitEffect(const XMFLOAT3& Hitpos, const XMFLOAT3& pos)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = Hitpos;
		data.delay = 0;
		data.number = 40;
		data.lifeTime = 40;
		XMStoreFloat3(&data.direction, -XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(GameManager::GetpPlayer()->GetPosition())) - XMLoadFloat3(&pos)));
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.15f;
		data.speedRnd = 0.8f;
		data.size = XMFLOAT2(1.5f, 1.5f);
		data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
		data.scale = XMFLOAT2(1.05f, 1.05f);
		data.color = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);
		data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
		VFX::Start(data);
	}

	//���ʂƂ��̃G�t�F�N�g
	void DieEffect(const XMFLOAT3& pos, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = pos;
		data.delay = 0;
		data.number = 250;
		data.lifeTime = 100;
		data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
		data.direction = VectorToFloat3(dir);
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