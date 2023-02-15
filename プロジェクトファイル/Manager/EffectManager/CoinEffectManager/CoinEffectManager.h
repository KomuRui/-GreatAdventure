#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Coinのエフェクトを管理する
/// </summary>
namespace CoinEffectManager
{

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	/// <param name="handle">エフェクト番号</param>
	void HitEffect(const int& handle);

}