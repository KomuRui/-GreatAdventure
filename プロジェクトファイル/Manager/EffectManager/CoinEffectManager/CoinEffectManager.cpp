#include "CoinEffectManager.h"
#include "../../../Engine/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/VFX.h"

/// <summary>
/// Coinのエフェクトを管理する
/// </summary>
namespace CoinEffectManager
{
	/////////////////////////////////変数/////////////////////////////////////

	//エフェクト表示するのに必要なデータ
	//std::vector<Particle*> pEffectData_;

	/////////////////////////////////関数/////////////////////////////////////

	//追加
	int Add(GameObject* coin)
	{
		//新たに追加
		/*pEffectData_.push_back(Instantiate<Particle>(coin));
		return (int)pEffectData_.size() - 1;*/
		return 1;
	}

	/// <summary>
	/// 解放
	/// </summary>
	void Release(const int& handle)
	{
		/*for (int i = 0; i < pEffectData_.size(); i++)
		{
			if (i != handle)
			{
				pEffectData_[i]->KillMe();
				break;
			}
		}*/
	}

	//すべて解放
	void AllRelease()
	{
		////削除
		//for (auto i = pEffectData_.begin(); i != pEffectData_.end(); i++)
		//{
		//	(*i)->KillMe();
		//}

		////空にする
		//pEffectData_.clear();
	}

	//当たった時のエフェクト
	void HitEffect(const int& handle)
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
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
}