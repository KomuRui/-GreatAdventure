#pragma once

/// <summary>
/// Playerの音を管理する
/// </summary>
namespace PlayerAudioManager
{
	/// <summary>
	/// 初期化
	///</summary>
	void Initialize();

	/// <summary>
	/// シーン遷移の時の初期化
	/// </summary>
	void SceneTransitionInitialize();

	/// <summary>
	/// 回転音
	/// </summary>
	void RotationAudio();

	/// <summary>
	/// 攻撃当たった時の音
	/// </summary>
	void AttackHitAudio();

	/// <summary>
	/// ダメージくらった時の音
	/// </summary>
	void DamageAudio();

	/// <summary>
	/// ジャンプ音
	/// </summary>
	void JumpAudio();

	/// <summary>
	/// 着地音
	/// </summary>
	void JumpLandAudio();

	/// <summary>
	/// ブロックヒット音
	/// </summary>
	void BlockHitAudio();
}