#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// 様々なエフェクトを管理する
/// </summary>
namespace OtherEffectManager
{
	/// <summary>
	/// 水流エフェクト
	/// </summary>
	/// <param name="pos">発生させたいポジション</param>
	/// <param name="dir">水流の方向</param>
	int WaterCurrentEffect(const XMFLOAT3& pos,const XMFLOAT3& dir);

	/// <summary>
	/// 爆発エフェクト
	/// </summary>
	/// <param name="Hitpos">エフェクトを発生させたい位置</param>
	void ExplosionEffect(const XMFLOAT3& pos);
}