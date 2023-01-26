#pragma once
#include "../../../Engine/Particle.h"
#include "../../../Engine/GameObject.h"

/// <summary>
/// Coinのエフェクトを管理する
/// </summary>
namespace CoinEffectManager
{
	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="enemy">エフェクト使う敵のポインタ</param>
	/// <returns>エフェクト番号(エフェクト使うときに使う)</returns>
	int Add(GameObject* coin);

	/// <summary>
	/// 解放
	/// </summary>
	void Release(const int& handle);

	/// <summary>
	/// 全て解放
	/// </summary>
	void AllRelease();

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	/// <param name="handle">エフェクト番号</param>
	void HitEffect(const int& handle);

}