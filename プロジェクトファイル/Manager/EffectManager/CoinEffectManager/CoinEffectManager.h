#pragma once
#include "../../../Engine/GameObject/GameObject.h"

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