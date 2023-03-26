#include "PlayerEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// Playerのエフェクトを管理する
/// </summary>
namespace PlayerEffectManager
{

	//回転エフェクト
	void RotationEffect(int modelnum)
	{
		XMFLOAT3 Right = Model::GetBonePosition(modelnum, "Right2");//右
		XMFLOAT3 Left = Model::GetBonePosition(modelnum, "Left2");  //左

		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = Right;
		data.positionRnd = XMFLOAT3(0.3, 0.2, 0.3);
		data.delay = 0;
		data.number = 5;
		data.lifeTime = 50;
		data.speed = 0.04f;
		data.speedRnd = 0.8;
		data.size = XMFLOAT2(0.6, 0.6);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.00, 1.00);
		data.color = XMFLOAT4(0, 1, 1, 1);
		data.deltaColor = XMFLOAT4(0, -0.1, 0, -0.1);
		VFX::Start(data);

		data.position = Left;
		VFX::Start(data);

	}

	//落下エフェクト
	void FallEffect(XMFLOAT3 position)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = position;
		data.position.y -= 4;
		data.delay = 0;
		data.number = 180;
		data.lifeTime = 50;
		data.direction = XMFLOAT3(0, 0, 1);
		data.directionRnd = XMFLOAT3(0, 360, 0);
		data.speed = 0.2f;
		data.speedRnd = 0.45;
		data.size = XMFLOAT2(1, 1);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 1, 0.2);
		data.deltaColor = XMFLOAT4(0, 0, 0, -0.004);
		VFX::Start(data);
	}

	/// <summary>
	/// 死亡ポジション
	/// </summary>
	void DieEffect(const XMFLOAT3& position, const XMVECTOR& dir)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/Cloud.png";
		data.position = position;
		data.delay = 0;
		data.number = 350;
		data.lifeTime = 100;
		data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
		data.direction = VectorToFloat3(dir);
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedRnd = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.2, 0.2);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		VFX::Start(data);
	}

	//吸収エフェクト
	void AbsorptionEffect(const XMFLOAT3& pos, const XMVECTOR& dir, const XMVECTOR& up)
	{
		EmitterData data;
		data.textureFileName = "Image/Effect/flashB_B.png";
		data.positionRnd = XMFLOAT3(4, 4, 4);
		data.position = Float3Add(pos,VectorToFloat3(-up * 5));
		data.delay = 1;
		data.number = 2;
		data.lifeTime = 180;
		data.direction = VectorToFloat3(dir);
		data.spin = XMFLOAT3(0, 0, 5);
		data.speed = 0.2f;
		data.isBillBoard = true;
		data.speedRnd = 0.8;
		data.size = XMFLOAT2(1.2, 1.2);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0, 1);
		data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 30);
		VFX::Start(data);

		EmitterData data2;
		data2.textureFileName = "Image/Effect/waterdrop.png";
		data2.position =  SubTract(pos,VectorToFloat3(-up * 0.7f));
		data2.delay = 0;
		data2.number = 1;
		data2.speed = 0.0f;
		data2.isBillBoard = false;
		data2.rotate.x = 70;
		data2.lifeTime = 10000;
		data2.size = XMFLOAT2(5.5, 5.5);
		data2.color = XMFLOAT4(1, 1, 0, 1);
		VFX::Start(data2);
	}
}