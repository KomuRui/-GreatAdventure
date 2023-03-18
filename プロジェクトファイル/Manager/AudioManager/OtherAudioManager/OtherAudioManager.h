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
}