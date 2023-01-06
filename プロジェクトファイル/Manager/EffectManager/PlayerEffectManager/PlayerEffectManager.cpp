#include "PlayerEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"

/// <summary>
/// Playerのエフェクトを管理する
/// </summary>
namespace PlayerEffectManager
{
	/////////////////////////////////変数/////////////////////////////////////

	//エフェクト表示するのに必要な変数
	Particle* pEffect_;

	/////////////////////////////////関数/////////////////////////////////////

	//初期化
	void Initialize(GameObject* player)
	{
		ARGUMENT_INITIALIZE(pEffect_, Instantiate<Particle>(player));
	}

	//解放
	void AllRelease()
	{
		//nullptrならreturn
		if (pEffect_ == nullptr) return;

		//削除
		pEffect_->KillMe();
	}

	//回転エフェクト
	void RotationEffect(int modelnum)
	{
		XMFLOAT3 Right = Model::GetBonePosition(modelnum, "Right2");//右
		XMFLOAT3 Left = Model::GetBonePosition(modelnum, "Left2");  //左

		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = Right;
		data.positionErr = XMFLOAT3(0.3, 0.2, 0.3);
		data.delay = 0;
		data.number = 5;
		data.lifeTime = 50;
		data.speed = 0.04f;
		data.speedErr = 0.8;
		data.size = XMFLOAT2(0.6, 0.6);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.00, 1.00);
		data.color = XMFLOAT4(0, 1, 1, 1);
		data.deltaColor = XMFLOAT4(0, -0.1, 0, -0.1);
		pEffect_->Start(data);


		data.position = Left;
		pEffect_->Start(data);
	}

	//落下エフェクト
	void FallEffect(XMFLOAT3 position)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = position;
		data.position.y -= 4;
		data.delay = 0;
		data.number = 180;
		data.lifeTime = 50;
		data.dir = XMFLOAT3(0, 0, 1);
		data.dirErr = XMFLOAT3(0, 360, 0);
		data.speed = 0.2f;
		data.speedErr = 0.45;
		data.size = XMFLOAT2(1, 1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 1, 0.2);
		data.deltaColor = XMFLOAT4(0, 0, 0, -0.004);
		pEffect_->Start(data);
	}
}