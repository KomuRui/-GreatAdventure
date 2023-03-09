#include "OtherEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// �l�X�ȃG�t�F�N�g���Ǘ�����
/// </summary>
namespace OtherEffectManager
{
	//�����G�t�F�N�g
	int WaterCurrentEffect(const XMFLOAT3& pos, const XMFLOAT3& dir)
	{
		EmitterData data;

		data.textureFileName = "Water.png";
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

		//���H
		data.textureFileName = "defaultParticle.png";
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