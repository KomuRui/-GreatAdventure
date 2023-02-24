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

	/// <summary>
	/// コインを吸収されるエフェクト
	/// </summary>
	/// <param name="pos">発生ポジション</param>
	/// <param name="dir">方向</param>
	/// <param name="up">キャラの上方向</param>
	void AbsorptionEffect(const XMFLOAT3& pos, const XMVECTOR& dir,const XMVECTOR& up);
}

