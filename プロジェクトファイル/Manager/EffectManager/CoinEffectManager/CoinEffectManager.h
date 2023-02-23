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
	void HitEffect();

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	/// <param name="pos">発生させたい位置</param>
	void HitEffect(XMFLOAT3 pos);

}