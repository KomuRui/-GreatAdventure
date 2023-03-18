#pragma once

/// <summary>
/// 様々な音を管理する
/// </summary>
namespace OtherAudioManager
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
	/// クリック音
	/// </summary>
	void ClickAudio();

	/// <summary>
	/// ワープヒット音
	/// </summary>
	void WarpHitAudio();

	/// <summary>
	/// ワープショット音
	/// </summary>
	void WarpShootAudio();

	/// <summary>
	/// ゲームオーバー音
	/// </summary>
	void GameOverAudio();
}