#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// Playerのエフェクトを管理する
/// </summary>
namespace PlayerEffectManager
{

	/// <summary>
	/// 回転エフェクト
	/// </summary>
	/// <param name="modelnum">playerのモデル番号</param>
	void RotationEffect(int modelnum);

	/// <summary>
	/// 落下エフェクト
	/// </summary>
	/// <param name="position">エフェクトを発生させたいポジション</param>
	void FallEffect(XMFLOAT3 position);

	/// <summary>
	/// 死亡ポジション
	/// </summary>
	void DieEffect(const XMFLOAT3& position, const XMVECTOR& dir);
}

