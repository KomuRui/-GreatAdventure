#pragma once
#include "../../../Engine/GameObject.h"

/// <summary>
/// Enemyのエフェクトを管理する
/// </summary>
namespace EnemyEffectManager
{

	/// <summary>
	/// 当たった時のエフェクト
	/// </summary>
	/// <param name="handle">エフェクト番号</param>
	/// <param name="Hitpos">エフェクトを発生させたい位置</param>
	/// <param name="pos">敵の位置</param>
	void HitEffect(const XMFLOAT3& Hitpos, const XMFLOAT3& pos);

	/// <summary>
	/// 死ぬときのエフェクト
	/// </summary>
	/// <param name="handle">エフェクト番号</param>
	/// <param name="pos">敵の位置</param>
	/// <param name="dir">エフェクトの方向</param>
	void DieEffect(const XMFLOAT3& pos, const XMVECTOR& dir);
}